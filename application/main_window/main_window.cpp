#include "main_window.hpp"

#include "alerts_page.hpp"
#include "charts_page.hpp"
#include "connections_page.hpp"
#include "logbook_page.hpp"
#include "scenarios_page.hpp"
#include "sensors_page.hpp"
#include "settings_page.hpp"

main_window::main_window( const std::string&  name,
						  script::engine::ptr ngn_ptr,
						  QWidget*			  parent )
	: QMainWindow( parent )
	, script::object{ name, ngn_ptr }

{
	Q_INIT_RESOURCE( main_window );

	_stkd_wdgt		 = new QStackedWidget{ this };
	_tl_bar			 = new QToolBar{ this };

	_tl_bar->setIconSize( { 32, 32 } );
	_tl_bar->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
	_tl_bar->setMovable( false );

	addToolBar( Qt::LeftToolBarArea, _tl_bar );
	setCentralWidget( _stkd_wdgt );

	_pages_tree_root = std::make_shared< _nd_t >( _nd_t{
	  { .name		 = "",
		.description = "don't use this node ",
		.children	 = {
			 _nd_t{ { .name = "alerts",
					  .data = { ._page_ptr
								= new alerts_page{ "alerts", _ngn_ptr, this } } } },
			 _nd_t{ { .name = "sensors",
					  .data = { ._page_ptr
								= new sensors_page{ "sensors", _ngn_ptr, this } } } },
			 _nd_t{ { .name = "connections",
					  .data
					  = { ._page_ptr
						  = new connections_page{ "connections", _ngn_ptr, this } } } },
			 _nd_t{ { .name = "charts",
					  .data = { ._page_ptr
								= new charts_page{ "charts", _ngn_ptr, this } } } },
			 _nd_t{ { .name = "logbook",
					  .data = { ._page_ptr
								= new logbook_page{ "logbook", _ngn_ptr, this } } } },
			 _nd_t{
			   { .name = "scenarios",
				 .data = { ._page_ptr
						   = new scenarios_page{ "scenarios", _ngn_ptr, this } } } },
			 _nd_t{ { .name = "settings",
					  .data = {
						._page_ptr
						= new settings_page{ "settings", _ngn_ptr, this } } } } } }
	  } );

	std::function< void( _nd_t& ) > traverse_nodes{};

	traverse_nodes = [ this, &traverse_nodes ]( _nd_t& node ) -> void {
		for ( auto& child : node._children )
			{
				_stkd_wdgt->addWidget( child._data._page_ptr );

				auto icon{ QIcon(
					QPixmap{ std::string{ ":/main_window/icons/"
										  + child.get_full_path_name() + ".png" }
								 .c_str() }
						.scaled( _tl_bar->iconSize(),
								 Qt::AspectRatioMode::KeepAspectRatio ) ) };

				auto action_ptr{ _tl_bar->addAction( icon, child._name.c_str() ) };
				auto page_name{ child.get_full_path_name() };

				QObject::connect( action_ptr, &QAction::triggered, [ this, page_name ]() {
					auto G{ _ngn_ptr->globals() };
					auto page_obj{ _sys_pages_lua_obj [ page_name ] };
					auto mn_wndw_obj{ G [ "cascade_client" ][ "main_window" ] };
					auto func{
						G [ "cascade_client" ][ "main_window" ][ "set_current" ]
					};
					func( mn_wndw_obj, page_obj );
				} );
				
				_sys_pages_lua_obj.insert(
					{ page_name, child._data._page_ptr->create_lua_object_from_this() } );

				traverse_nodes( child );
			}
	};
	traverse_nodes( *_pages_tree_root );

	self_register();
}

main_window::~main_window() { Q_CLEANUP_RESOURCE( main_window ); }

sol::object
main_window::create_lua_object_from_this() const
{
	return sol::make_object( _ngn_ptr->lua_state(), this );
}

void
main_window::self_register()
{
	if ( can_self_register() )
		{
			auto type{ _ngn_ptr->new_usertype< main_window >( class_name() ) };

			type [ "pages" ]			= &main_window::_sys_pages_lua_obj;

			type [ "set_current" ] = []( main_window* self, const sol::object obj ) {
				auto page_opt{ obj.as< sol::optional< page* > >() };
				if ( page_opt )
					{
						auto page_ptr{ *page_opt };

						auto a = page_ptr->_name;
						auto b = self->_sys_pages_lua_obj.contains( a );
						auto c = self->_sys_pages_lua_obj [ a ] == obj;

						if ( auto page_name{ page_ptr->_name };
							 self->_sys_pages_lua_obj.contains( page_name )
							 && self->_sys_pages_lua_obj [ page_name ] == obj )
							{
								self->_stkd_wdgt->setCurrentWidget( page_ptr );
							}
						else
							{
								std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"
										  << std::endl;
							}
					}
				else
					{
						std::cout << "passed obj to 'set_current_page' function can't be "
									 "converted to page* pointer";
					}
			};
		}
}
