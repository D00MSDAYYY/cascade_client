#include "application.hpp"

application::application( int& argc, char** argv )
	: QApplication{ argc, argv }
	, scripting::object{ "cascade_client", scripting::engine::make_real_engine() }
{
	setStyle( "Fusion" );
	
	_ngn_ptr->open_libraries( sol::lib::base );

	_dbg_wndw = std::shared_ptr< debug_console >(
		new debug_console{ "debug_console", _ngn_ptr } );

	_mn_wndw
		= std::shared_ptr< main_window >( new main_window{ "main_window", _ngn_ptr } );

	_dbg_wndw->show();
	_mn_wndw->show();

	_mn_wndw->resize( 1'024, 768 );
	_mn_wndw->setMinimumSize( 800, 600 );

	self_register();
}

void
application::self_register()
{
	if ( can_self_register() )
		{
			_ngn_ptr->globals() [ _name ] = this;
			
			auto type{ _ngn_ptr->new_usertype< application >( class_name() ) };
			
			type [ _mn_wndw->_name ] = &application::_mn_wndw;
			
		}
}
