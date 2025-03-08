#include "main_window.hpp"
#include "script_engine.hpp"

#include <QApplication>

int
main( int argc, char** argv )
{
	QApplication app( argc, argv );
	app.setStyle( "Windows" );
	app.setStyleSheet( R"(
			QMainWindow, QDialog, QWidget {
				background-color: rgb(255, 255, 255); /* Белый фон */
			}

            QToolBar {
                background-color: #C0C0C0; /* Серый фон */
                border: 1px solid #808080; /* Граница */
                spacing: 1px; /* Расстояние между элементами */
                padding: 1px; /* Внутренние отступы */
            }

            QToolButton {
                background-color: #C0C0C0; /* Серый фон */
                border: 2px outset #A0A0A0; /* Внешняя рамка */
                color: black; /* Черный текст */
                margin: 2px; /* Внешний отступ */
                font-family: "MS Shell Dlg", sans-serif; /* Шрифт Windows 2000 */
                min-width: 70px; /* Минимальная ширина кнопки */
                min-height: 30px; /* Минимальная высота кнопки */
            }

            QToolButton:hover {
                background-color: #A0A0A0; /* Цвет фона при наведении */
                border: 1px solid #808080; /* Граница при наведении */
            }

            QToolButton:pressed {
                background-color: #808080; /* Цвет фона при нажатии */
                border: 1px solid #404040; /* Граница при нажатии */
            }

            QPushButton {
                background-color: #C0C0C0; /* Серый фон */
                border: 2px outset #A0A0A0; /* Внешняя рамка */
                color: black; /* Черный текст */
                padding: 5px; /* Отступы внутри кнопки */
                font-family: "MS Shell Dlg", sans-serif; /* Шрифт Windows 2000 */
            }

            QPushButton:hover {
                background-color: #D0D0D0; /* Светлее при наведении */
                border: 2px outset #B0B0B0; /* Сохранение внешней рамки при наведении */
            }

            QPushButton:pressed {
                background-color: #A0A0A0; /* Цвет фона при нажатии */
                border: 1px solid #808080; /* Граница при нажатии */
            }

            QComboBox {
                background-color: #C0C0C0; /* Серый фон */
                border: 1px solid #808080; /* Граница */
                padding: 2px; /* Отступы внутри */
                font-family: "MS Shell Dlg", sans-serif; /* Шрифт Windows 2000 */
                min-width: 100px; /* Минимальная ширина */
            }
			
			QListView{
				color: black;
			}
			QComboBox QAbstractItemView {
				outline: 0px solid gray;   /*  The virtual frame of the selected item */
				border: 1px solid black;   /*  Border of the entire drop-down form */
				background-color: gray;   /*  Whole drop-down form background color */
				selection-background-color:rgb(21, 21, 186) ;   /*  The whole drop-down window is selected from the background color of the item */
				font-color: black;
			}

            QLabel {
                color: black; /* Черный текст */
                font-family: "MS Shell Dlg", sans-serif; /* Шрифт Windows 2000 */
            }

            QRadioButton {
                color: black; /* Черный текст */
                font-family: "MS Shell Dlg", sans-serif; /* Шрифт Windows 2000 */
            }

            QRadioButton::indicator {
                width: 16px; /* Размер индикатора */
                height: 16px; /* Размер индикатора */
            }

             QGroupBox {
                border: 1px solid gray; /* Граница */
                margin-top: 1ex; /* Отступ сверху */
                font-family: "MS Shell Dlg", sans-serif; /* Шрифт Windows 2000 */
                padding-top: 10px; /* Отступ сверху внутри QGroupBox */
            }

            QGroupBox::title {
                subcontrol-origin: margin;
                subcontrol-position: top left; /* Заголовок вверху слева */
                padding: 1px; /* Отступы вокруг текста заголовка */
                background-color: white; /* Прозрачный фон заголовка */
                color: black; /* Черный текст */
            }

            QScrollBar::handle {
                background-color: #C0C0C0; /* Серый фон */
                border: 2px outset #A0A0A0; /* Внешняя рамка */
                color: black; /* Черный текст */
                padding: 5px; /* Отступы внутри кнопки */
                font-family: "MS Shell Dlg", sans-serif; /* Шрифт Windows 2000 */
            }
           
)" );

	auto mw{ new main_window() };
	mw->setFixedSize( 1'024 * 2 / 3, 600 * 2 / 3 );
	mw->show();

	return app.exec();
}
