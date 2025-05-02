#include "ui_toolkit.hpp"

#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <map>

void
ui_toolkit::register_in_lua( const scripting::engine::ptr& ngn_ptr )
{
	if ( scripting::object::can_register_in_lua< ui_toolkit >( ngn_ptr ) )
		{
			std::vector< std::string > COLORS{ "white", "gray", "black", "yellow",
											   "red",	"blue", "green", "gray" };

			std::map< std::string, QSizePolicy::Policy > SIZE_POLICIES{
				{ "Fixed",	   QSizePolicy::Fixed	  },
				{ "Minimum",	 QSizePolicy::Minimum	  },
				{ "Maximum",	 QSizePolicy::Maximum	  },
				{ "Preferred", QSizePolicy::Preferred },
				{ "Expanding", QSizePolicy::Expanding },
				{ "Ignored",	 QSizePolicy::Ignored	  }
			};

			auto ui_tbl{ ngn_ptr->create_named_table( "ui" ) };
			std::cout << "vvvvvv" << ui_tbl.valid() << std::endl;

			ui_tbl.new_usertype< QWidget >(
				"QWidget",
				sol::factories( []( std::optional< QWidget* > parent ) {
					return new QWidget{ parent.value_or( nullptr ) };
				} ),

				"setLayout",
				[]( QWidget* self, QLayout* lyt ) { self->setLayout( lyt ); },

				"setSizePolicy",
				[ SIZE_POLICIES ]( QWidget*			  self,
								   const std::string& horiz,
								   const std::string& vert ) {
					if ( SIZE_POLICIES.contains( horiz )
						 and SIZE_POLICIES.contains( vert ) )
						{
							self->setSizePolicy( SIZE_POLICIES.at( horiz ),
												 SIZE_POLICIES.at( vert ) );
						}
				},

				"show",
				&QWidget::show,

				"setStyleSheet",
				[]( QWidget* self, const std::string& text ) {
					self->setStyleSheet( text.c_str() );
				},

				"setColor",
				[ COLORS ]( QWidget* self, const std::string& color ) {
					if ( std::find( COLORS.begin(), COLORS.end(), color )
						 != COLORS.end() )
						{
							self->setStyleSheet(
								QString( "QPushButton { background-color: %1; }" )
									.arg( color.c_str() ) );
						}
				},

				"setFontSize",
				[]( QWidget* self, int size ) {
					auto font{ self->font() };
					font.setPointSize( size );
					self->setFont( font );
				},

				sol::base_classes,
				sol::bases< QObject >() );


			ui_tbl.new_usertype< QLabel >(
				"QLabel",
				sol::factories(
					[]( std::optional< QWidget* > parent ) {
						auto ptr{ new QLabel{ parent.value_or( nullptr ) } };
						ptr->setSizePolicy( QSizePolicy::Expanding,
											QSizePolicy::Expanding );
						return ptr;
					},
					[]( const std::string& text, std::optional< QWidget* > parent ) {
						auto ptr{
							new QLabel{ text.c_str(), parent.value_or( nullptr ) }
						};
						ptr->setSizePolicy( QSizePolicy::Expanding,
											QSizePolicy::Expanding );
						return ptr;
					} ),

				"setText",
				[]( QLabel* self, const std::string& text ) {
					self->setText( text.c_str() );
				},

				"text",
				[]( QLabel* self ) { return self->text().toStdString(); },

				"clear",
				&QLabel::clear,

				sol::base_classes,
				sol::bases< QFrame, QWidget, QObject >() );

			// Регистрация QPushButton
			ui_tbl.new_usertype< QPushButton >(
				"QPushButton",
				sol::factories(
					[]( std::optional< QWidget* > parent ) {
						return new QPushButton{ parent.value_or( nullptr ) };
					},
					[]( const std::string& text, std::optional< QWidget* > parent ) {
						return new QPushButton{ text.c_str(),
												parent.value_or( nullptr ) };
					} ),

				"setText",
				[]( QPushButton* self, const std::string& text ) {
					self->setText( text.c_str() );
				},

				"text",
				[]( QPushButton* self ) { return self->text().toStdString(); },

				"setEnabled",
				&QPushButton::setEnabled,

				"isEnabled",
				&QPushButton::isEnabled,

				"click",
				&QPushButton::click,

				"on_clicked", //! don't register too much signal, just nessesary ones
				&QPushButton::clicked,

				sol::base_classes,
				sol::bases< QAbstractButton, QWidget, QObject >() );

			ui_tbl.new_usertype< QHBoxLayout >(
				"QHBoxLayout",
				sol::factories( []( std::optional< QWidget* > parent ) {
					return new QHBoxLayout{ parent.value_or( nullptr ) };
				} ),

				"addWidget",
				[]( QHBoxLayout* self, QWidget* wgt ) { self->addWidget( wgt ); },

				"addStretch",
				&QHBoxLayout::addStretch,

				"count",
				&QHBoxLayout::count,

				sol::base_classes,
				sol::bases< QBoxLayout, QLayout, QLayoutItem, QObject >() );
		}
	std::cout << _class_name << "\t is registered" << std::endl;
}
