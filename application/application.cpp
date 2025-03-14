#include "application.hpp"

#include "main_window.hpp"
#include "script_engine.hpp"

application::application( int& argc, char** argv )
	: QApplication{ argc, argv }
{
	_scrpt_ngn.reset( new script_engine{} );
	_mn_wndw.reset( new main_window{ _scrpt_ngn } );
	_mn_wndw->show();
}
