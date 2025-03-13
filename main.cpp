#include "main_window.hpp"

#include <QApplication>
#include <memory>

int
main( int argc, char** argv )
{
	auto app{
	  QApplication{ argc, argv }
	 };
	auto se{ std::make_shared< script_engine >() };
	auto mw{ std::make_shared< main_window >( se ) };
	mw->setFixedSize( 1'024 * 2 / 3, 600 * 2 / 3 );
	mw->show();
	app.setStyle( "Fusion" );
	
	return app.exec();
}

