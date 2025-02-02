#include "main_window.hpp"

#include <QApplication>
#include <QStyleFactory>
#include <iostream>
int main(int argc , char** argv ){
	
	QApplication app(argc, argv);
	app.setStyleSheet("QMainWindow {"
					  "    background-color:rgb(255, 255, 255);" /* Серый фон */
					  "}"
					  "QToolBar {"
					  "    background-color: #C0C0C0;"			 /* Серый фон */
					  "    border: 1px solid #808080;"			 /* Граница */
					  "    spacing: 2px;"						 /* Расстояние между элементами */
					  "    padding: 2px;"						 /* Внутренние отступы */
					  "}"
					  "QToolButton {"
					  //   "    font-family: 'Arial'; "
					  "    font-size: 14px; "
					  "    font-weight: bold;"
					  "    background-color: transparent;" /* Прозрачный фон */
					  "    border: 1px solid transparent;" /* Прозрачная граница */
					  "    padding: 2px;"				   /* Внутренние отступы */
					  "    margin: 1px;"				   /* Внешние отступы */
					  "}"
					  "QToolButton:hover {"
					  "    background-color: #A0A0A0;"	   /* Цвет фона при наведении */
					  "    border: 1px solid #808080;"	   /* Граница при наведении */
					  "}"
					  "QToolButton:pressed {"
					  "    background-color: #808080;"	   /* Цвет фона при нажатии */
					  "    border: 1px solid #404040;"	   /* Граница при нажатии */
					  "}"

	);

	auto mw{new main_window()};
    mw->show();


	return app.exec();
}