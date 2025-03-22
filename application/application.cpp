#include "application.hpp"

#include "main_window.hpp"

application::application( int& argc, char** argv )
	: QApplication{ argc, argv }
{

	_mn_wndw.reset( new main_window{} );
	_mn_wndw->show();
}
