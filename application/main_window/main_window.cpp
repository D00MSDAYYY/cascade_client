#include "main_window.hpp"

#include "alerts_page.hpp"
#include "charts_page.hpp"
#include "connections_page.hpp"
#include "logbook_page.hpp"
#include "scenarios_page.hpp"
#include "sensors_page.hpp"
#include "settings_page.hpp"

main_window::main_window( const scripting::engine::ptr ngn_ptr, QWidget* parent )
	: QMainWindow( parent )
	, scripting::object{ ngn_ptr }

{
	Q_INIT_RESOURCE( main_window );
	register_in_lua( _ngn_ptr.value() );

	_stkd_wdgt = new QStackedWidget{ this };
	_tl_bar	   = new QToolBar{ this };

	_tl_bar->setIconSize( { 32, 32 } );
	_tl_bar->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
	_tl_bar->setMovable( false );

	_tl_bar->setStyleSheet( R"(
    QToolButton:checked {
        background-color: palette(highlight);
    }
)" );

	addToolBar( Qt::LeftToolBarArea, _tl_bar );
	setCentralWidget( _stkd_wdgt );

	auto _fast_fill_node{ [this]< typename T >( const std::string& name ) {
		return _nd_t{
			{ .name = name, .data = { ._page_ptr = new T{ name, _ngn_ptr.value(), this } } }
		};
	} };

	_pages_tree_root = std::make_shared< _nd_t >( _nd_t{
	  { .name		 = "",
		.description = "don't use this node ",
		.children	 = {
			 _fast_fill_node.operator()< alerts_page >( "alerts" ),
			 _fast_fill_node.operator()< sensors_page >( "sensors" ),
			 _fast_fill_node.operator()< connections_page >( "connections" ),
			 _fast_fill_node.operator()< charts_page >( "charts" ),
			 _fast_fill_node.operator()< scenarios_page >( "scenarios" ),
			 _fast_fill_node.operator()< logbook_page >( "logbook" ),
			 _fast_fill_node.operator()< settings_page >( "settings" ),
		   } }
	} );

	std::function< void( _nd_t& ) > traverse_nodes{};

	traverse_nodes = [ this, &traverse_nodes ]( _nd_t& node ) -> void {
		for ( auto& child : node._children )
			{
				auto path_str{ QString{ ":/main_window/icons/" }
							   + child.get_full_path_name().c_str() + ".png" };
				auto icon{ QIcon( QPixmap{ path_str }.scaled(
					_tl_bar->iconSize(),
					Qt::AspectRatioMode::KeepAspectRatio ) ) };

				auto action_ptr{ _tl_bar->addAction( icon, child._name.c_str() ) };
				action_ptr->setCheckable( true );

				auto page_name{ child.get_full_path_name() };
				_stkd_wdgt->addWidget( child._data._page_ptr );

				QObject::connect(
					action_ptr,
					&QAction::triggered,
					[ this, page_ptr = child._data._page_ptr, action_ptr ]() {
						for ( const auto& action : _tl_bar->actions() )
							{
								action->setChecked( false );
							}
						action_ptr->setChecked( true );
						set_current_page( page_ptr );
					} );
				action_ptr->trigger();
				// _pages.insert( { page_name, child._data._page_ptr } );

				traverse_nodes( child );
			}
	};
	traverse_nodes( *_pages_tree_root );
}

main_window::~main_window() { Q_CLEANUP_RESOURCE( main_window ); }

std::map< std::string, sol::object >
main_window::get_pages()
{
	std::map< std::string, sol::object > tmp{};
	for ( int i = 0; i < _stkd_wdgt->count(); ++i )
		{
			auto wgt{ _stkd_wdgt->widget( i ) };
			auto page_ptr{ qobject_cast< page* >( wgt ) };
			tmp.insert( { page_ptr->get_name(), page_ptr->make_lua_object_from_this() } );
		}
	return tmp;
}

void
main_window::add_page( page* page )
{
	//! TODO add safety checks and reports
	_stkd_wdgt->addWidget( page );
}

void
main_window::remove_page( page* page )
{
	//! TODO add safety checks and reports
	_stkd_wdgt->removeWidget( page );
}

void
main_window::set_current_page( page* page )
{
	//! TODO add safety checks and reports
	_stkd_wdgt->setCurrentWidget( page );
}

void
main_window::register_in_lua( const scripting::engine::ptr& ngn_ptr )
{
	if ( can_register_in_lua< main_window >( ngn_ptr ) )
		{
			auto type{ ngn_ptr->new_usertype< main_window >( _class_name ) };

			type [ "get_pages" ] = &main_window::get_pages;

			type [ "add_page" ]	 = []( main_window* self, const sol::object obj ) {
				 if ( auto page_ptr{ obj.as< sol::optional< page* > >() }; page_ptr )
					 {
						 self->add_page( *page_ptr );
					 }
			};
			type [ "remove_page" ] = []( main_window* self, const sol::object obj ) {
				if ( auto page_ptr{ obj.as< sol::optional< page* > >() }; page_ptr )
					{
						self->remove_page( *page_ptr );
					}
			};

			type [ "set_current_page" ] = []( main_window* self, const sol::object obj ) {
				if ( auto page_ptr{ obj.as< sol::optional< page* > >() }; page_ptr )
					{
						self->set_current_page( *page_ptr );
					}
			};
		}
	std::cout << _class_name << "\t is registered" << std::endl;
}
