#include "main_window.hpp"

#include "alerts_page.hpp"
#include "charts_page.hpp"
#include "connections_page.hpp"
#include "logbook_page.hpp"
#include "scenarios_page.hpp"
#include "sensors_page.hpp"

main_window::main_window( const std::string&  name,
						  script::engine::ptr ngn_ptr,
						  QWidget*			  parent )
	: QMainWindow( parent )
	, script::object{ name, ngn_ptr }

{
	Q_INIT_RESOURCE( main_window );

	_stkd_wgt = new QStackedWidget{ this };
	_tl_bar	  = new QToolBar{ this };

	_tl_bar->setIconSize( { 32, 32 } );
	_tl_bar->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
	_tl_bar->setMovable( false );


	for ( const auto& [ page_name, page_ptr ] : std::map< std::string, QWidget* >{
			{ "alerts",		new alerts_page{ "alerts_page", _ngn_ptr, this }			 },
			{ "sensors",	 new sensors_page{ "sensors_page", _ngn_ptr, this }			},
			{ "connections", new connections_page{ "connections_page", _ngn_ptr, this } },
			{ "charts",		new charts_page{ "charts_charts", _ngn_ptr, this }		   },
			{ "logbook",	 new logbook_page{ "logbook_page", _ngn_ptr, this }			},
			{ "scenarios",   new scenarios_page{ "scenarios_page", _ngn_ptr, this }	  },
			{ "settings",	  new QWidget{ this }										  }
	} )
		{
			auto path_str{ ":/main_window/icons/" + page_name + ".png" };
			// TODO
			////////////////////////////////////////
			// //
			// switch to actions_tree nodes    //
			// //
			////////////////////////////////////////
			auto action{ _tl_bar->addAction(
				QIcon( QPixmap{ { path_str.c_str() } }.scaled(
					_tl_bar->iconSize(),
					Qt::AspectRatioMode::KeepAspectRatio ) ),
				page_name.c_str() ) };

			page_ptr->setObjectName( page_name );
			_stkd_wgt->addWidget( page_ptr );

			QObject::connect( action, &QAction::triggered, [ this, page_ptr ]() {
				_stkd_wgt->setCurrentWidget( page_ptr );
			} );

			sol::object obj{ sol::lua_nil };
			if ( page_name == "alerts" )
				obj = sol::make_object( _ngn_ptr->lua_state(),
										dynamic_cast< alerts_page* >( page_ptr ) );
			else if ( page_name == "charts" )
				obj = sol::make_object( _ngn_ptr->lua_state(),
										dynamic_cast< charts_page* >( page_ptr ) );
			else if ( page_name == "connections" )
				obj = sol::make_object( _ngn_ptr->lua_state(),
										dynamic_cast< connections_page* >( page_ptr ) );
			else if ( page_name == "logbook" )
				obj = sol::make_object( _ngn_ptr->lua_state(),
										dynamic_cast< logbook_page* >( page_ptr ) );
			else if ( page_name == "scenarios" )
				obj = sol::make_object( _ngn_ptr->lua_state(),
										dynamic_cast< scenarios_page* >( page_ptr ) );
			else if ( page_name == "sensors" )
				obj = sol::make_object( _ngn_ptr->lua_state(),
										dynamic_cast< sensors_page* >( page_ptr ) );
			_pages_lua_obj.insert( { page_name, obj } );
		}

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
			
			type [ "pages" ]		   = &main_window::_pages_lua_obj;
			type [ "set_active_page" ] = []( main_window* self, const sol::object obj ) {
				for ( const auto& [ page_name, page_obj ] : self->_pages_lua_obj )
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
