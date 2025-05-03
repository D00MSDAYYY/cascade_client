#include "ui_toolkit.hpp"

#include <QFile>
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
			Q_INIT_RESOURCE( ui_toolkit );
			if ( QFile abstractbtn_file{ ":/ui_toolkit/scripts/qabstractbutton_extra.lua" },
				 dummy_file{ ":/ui_toolkit/scripts/dummy.lua" };
				 abstractbtn_file.open( QIODevice::ReadOnly | QIODevice::Text )
				 and dummy_file.open( QIODevice::ReadOnly | QIODevice::Text ) )
				{
					// /////////////////////////////////////////////////////////////////////
					std::vector< std::string >					 COLORS{ "white", "gray", "black", "yellow",
														 "red",	  "blue", "green", "gray" };
					// /////////////////////////////////////////////////////////////////////
					std::map< std::string, QSizePolicy::Policy > SIZE_POLICIES{
						{ "Fixed",	   QSizePolicy::Fixed	  },
						 { "Minimum",	  QSizePolicy::Minimum   },
						{ "Maximum",	 QSizePolicy::Maximum	  },
						 { "Preferred", QSizePolicy::Preferred },
						{ "Expanding", QSizePolicy::Expanding },
						 { "Ignored",	  QSizePolicy::Ignored   }
					};
					// /////////////////////////////////////////////////////////////////////

					auto ui_tbl{ ngn_ptr->create_named_table( "ui" ) };

					auto qwgt_type{ ui_tbl.new_usertype< QWidget >(
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
							if ( SIZE_POLICIES.contains( horiz ) and SIZE_POLICIES.contains( vert ) )
								{
									self->setSizePolicy( SIZE_POLICIES.at( horiz ),
														 SIZE_POLICIES.at( vert ) );
								}
						},

						"show",
						&QWidget::show,

						"setStyleSheet",
						[]( QWidget* self, const std::string& text ) { self->setStyleSheet( text.c_str() ); },

						"setColor",
						[ COLORS ]( QWidget* self, const std::string& color ) {
							if ( std::find( COLORS.begin(), COLORS.end(), color ) != COLORS.end() )
								{
									self->setStyleSheet( QString( "QPushButton { "
																  "background-color: %1; }" )
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
						sol::bases< QObject >() ) };

					auto qlabel_type{ ui_tbl.new_usertype< QLabel >(
						"QLabel",
						sol::factories(
							[]( std::optional< QWidget* > parent ) {
								auto ptr{ new QLabel{ parent.value_or( nullptr ) } };
								ptr->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
								return ptr;
							},
							[]( const std::string& text, std::optional< QWidget* > parent ) {
								auto ptr{
									new QLabel{ text.c_str(), parent.value_or( nullptr ) }
								};
								ptr->setSizePolicy( QSizePolicy::Expanding, QSizePolicy::Expanding );
								return ptr;
							} ),

						"setText",
						[]( QLabel* self, const std::string& text ) { self->setText( text.c_str() ); },

						"text",
						[]( QLabel* self ) { return self->text().toStdString(); },

						"clear",
						&QLabel::clear,

						sol::base_classes,
						sol::bases< QFrame, QWidget, QObject >() ) };

					// Регистрация QPushButton
					auto qabsbtn_type{ ui_tbl.new_usertype< QAbstractButton >(
						"QAbstractButton",

						"setText",
						[]( QAbstractButton* self, const std::string& text ) {
							self->setText( text.c_str() );
						},

						"text",
						[]( QAbstractButton* self ) { return self->text().toStdString(); },

						"setEnabled",
						&QAbstractButton::setEnabled,

						"isEnabled",
						&QAbstractButton::isEnabled,

						"click",
						&QAbstractButton::click,

						"_aux_connect_to_clicked",
						[]( sol::this_state	   ts,
							QAbstractButton*   self,
							const std::string& name,
							sol::function	   slot ) {
							const std::string CON_SLOTS_STR{ "connected_slots" };

							if ( auto cons_var{ self->property( CON_SLOTS_STR.c_str() ) };
								 cons_var.isValid() )
								{
									if ( auto cons{
										   cons_var.value< QMap< QString, QMetaObject::Connection > >() };
										 not cons.contains( name.c_str() ) )
										{
											auto con{ QObject::connect( self,
																		&QAbstractButton::clicked,
																		[ slot ]() { slot(); } ) };

											cons [ name.c_str() ] = con;
											self->setProperty( CON_SLOTS_STR.c_str(),
															   QVariant::fromValue( cons ) );
										}
									else
										{
											std::cout
												<< QString(
													   "'%1' property already contains slot with name '%2'" )
													   .arg( CON_SLOTS_STR )
													   .arg( name )
													   .toStdString();
										}
								}
							else
								{
									QMap< QString, QMetaObject::Connection > cons;

									auto con{ QObject::connect( self, &QAbstractButton::clicked, [ slot ]() {
										slot();
									} ) };
									cons [ name.c_str() ] = con;

									self->setProperty( CON_SLOTS_STR.c_str(), QVariant::fromValue( cons ) );
								}
						},

						sol::base_classes,
						sol::bases< QWidget, QObject >() ) };

					auto qpshbtn_type{ ui_tbl.new_usertype< QPushButton >(
						"QPushButton",
						sol::factories(
							[]( std::optional< QWidget* > parent ) {
								return new QPushButton{ parent.value_or( nullptr ) };
							},
							[]( const std::string& text, std::optional< QWidget* > parent ) {
								return new QPushButton{ text.c_str(), parent.value_or( nullptr ) };
							} ),

						sol::base_classes,
						sol::bases< QAbstractButton, QWidget, QObject >() ) };


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

					Q_CLEANUP_RESOURCE( ui_toolkit );

					std::cout << _class_name << "\t is registered" << std::endl;
				}
			else { std::cout << "can't open files" << std::endl; }
		}
	else { std::cout << "can't register ui_toolkit" << std::endl; }
}
