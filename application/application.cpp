#include "application.hpp"

#include "main_window.hpp"

application::application( int& argc, char** argv )
	: QApplication{ argc, argv }
	, script::object{ "cascade_client", script::engine::make_real_engine() }
{
	_ngn_ptr->open_libraries( sol::lib::base );
	_dbg_wndw = std::shared_ptr< debug_console >(
		new debug_console{ "debug_console", _ngn_ptr } );

	_mn_wndw = std::shared_ptr< main_window >( new main_window{
	  "main_window",
	  script::engine::make_proxy_engine( _ngn_ptr, _ngn_ptr->globals() ) } );

	_dbg_wndw->show();
	_mn_wndw->show();

	self_register();
}

void
application::self_register()
{
	_ngn_ptr->globals() [ _name ] = this;
	auto type{ _ngn_ptr->new_usertype< application >( "application" ) };
	type [ _mn_wndw->_name ] =  &application::_mn_wndw ;
}
