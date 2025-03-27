#include "application.hpp"

#include "main_window.hpp"

application::application( int& argc, char** argv )
	: QApplication{ argc, argv }
{
	_engine	 = script::engine::make_real_engine();
	_mn_wndw = std::make_shared< main_window >();

	_mn_wndw->show();
}
