#include <QApplication>

#include "main_window.hpp"
int main(int argc , char** argv ){
	
	QApplication app(argc, argv);
    app.setStyle("fusion");
    auto mw = new main_window();
    mw->show();

    return app.exec();

	
}