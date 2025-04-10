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

	_stkd_wgt	   = new QStackedWidget{ this };
	_tl_bar		   = new QToolBar{ this };

	auto fill_data = [ this ]( auto page_ptr ) -> _pg_d_t {
		return { page_ptr, sol::make_object( _ngn_ptr->lua_state(), page_ptr ) };
	};

	_sys_pages_tree_root = std::make_shared< _nd_t >( _nd_t{
	  { .name		 = "",
		.description = "don't use this node ",
		.children	 = {
			 _nd_t{
			   { .name = "alerts",
				 .data = fill_data( new alerts_page{ "alerts_page", _ngn_ptr, this } ) } },
			 _nd_t{
			   { .name = "sensors",
				 .data = fill_data( new sensors_page{ "sensors_page", _ngn_ptr, this } ) } },
			 _nd_t{ { .name = "connections",
					  .data = fill_data(
						  new connections_page{ "connections_page", _ngn_ptr, this } ) } },
			 _nd_t{
			   { .name = "charts",
				 .data = fill_data( new charts_page{ "charts_page", _ngn_ptr, this } ) } },
			 _nd_t{
			   { .name = "logbook",
				 .data = fill_data( new logbook_page{ "logbook_page", _ngn_ptr, this } ) } },
			 _nd_t{ { .name = "scenarios",
					  .data = fill_data(
						  new scenarios_page{ "scenarios_page", _ngn_ptr, this } ) } },
			 _nd_t{ { .name = "settings",
					  .data = fill_data(
						  new settings_page{ "settings_page", _ngn_ptr, this } ) } } } }
	  } );


	std::function< void( _nd_t& ) > traverse_nodes{};
	traverse_nodes = [ this, &traverse_nodes ]( _nd_t& node ) -> void {
		for ( auto& child : node._children )
			{
				auto path_str{ ":/main_window/icons/" + child.get_full_path_name()
							   + ".png" };

				auto icon{ QIcon( QPixmap{ { path_str.c_str() } }.scaled(
					_tl_bar->iconSize(),
					Qt::AspectRatioMode::KeepAspectRatio ) ) };

				auto action_ptr{ _tl_bar->addAction( icon, child._name.c_str() ) };

				child._data._page_ptr->setObjectName( child._name );
				_stkd_wgt->addWidget( child._data._page_ptr );

				QObject::connect( action_ptr, &QAction::triggered, [ this, child ]() {
					_stkd_wgt->setCurrentWidget( child._data._page_ptr );
				} );
				traverse_nodes( child );
			}
	};
	traverse_nodes( *_sys_pages_tree_root );


	_tl_bar->setIconSize( { 32, 32 } );
	_tl_bar->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
	_tl_bar->setMovable( false );

	addToolBar( Qt::LeftToolBarArea, _tl_bar );
	setCentralWidget( _stkd_wgt );
	self_register();
}

main_window::~main_window() { Q_CLEANUP_RESOURCE( main_window ); }

void
main_window::self_register()
{
	if ( can_self_register() )
		{
			auto type{ _ngn_ptr->new_usertype< main_window >( class_name() ) };

			type [ "pages" ]		   = &main_window::_sys_pages_lua_obj;
			type [ "set_active_page" ] = []( main_window* self, const sol::object obj ) {
				for ( const auto& [ page_name, page_obj ] : self->_sys_pages_lua_obj )
					{
						if ( page_obj == obj )
							{
								for ( auto i{ 0 }; i < self->_stkd_wgt->count(); ++i )
									{
										auto wgt{ self->_stkd_wgt->widget( i ) };
										if ( page_name == wgt->objectName() )
											{
												self->_stkd_wgt->setCurrentWidget( wgt );
												break;
											}
									}
								break;
							}
					}
			};
		}
}
