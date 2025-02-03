#include "main_window.hpp"

#include <QApplication>
#include <iostream>

int
main(int argc, char** argv)
{
	QApplication app(argc, argv);
	app.setStyle("Windows");
	app.setStyleSheet(R"(
QMainWindow {
    background-color: rgb(255, 255, 255); /* Белый фон */
}

QToolBar {
    background-color: #C0C0C0; /* Серый фон */
    border: 1px solid #808080; /* Граница */
    spacing: 2px; /* Расстояние между элементами */
    padding: 2px; /* Внутренние отступы */
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

QPushButton:pressed {
    background-color: #A0A0A0; /* Цвет фона при наведении */
    border: 1px solid #808080; /* Граница при наведении */
}

QPushButton:hover {
    background-color: #D0D0D0; /* Светлее при наведении */
    border: 2px outset #B0B0B0; /* Сохранение внешней рамки при наведении */
}

   QScrollBar::handle {
            background: #808080;
            border: 1px solid #404040;
        }
        QScrollBar::add-line,
        QScrollBar::sub-line {
            background: #C0C0C0;
            border: 1px solid #404040;
        }
        QScrollBar::add-line:vertical,
        QScrollBar::sub-line:vertical {
            height: 16px;
        }
        QScrollBar::add-line:horizontal,
        QScrollBar::sub-line:horizontal {
            width: 16px;
        }
        QScrollBar::up-arrow,
        QScrollBar::down-arrow,
        QScrollBar::left-arrow,
        QScrollBar::right-arrow {
            background: #404040;
            width: 7px;
            height: 7px;
        }
        QScrollBar::add-page,
        QScrollBar::sub-page {
            background: #C0C0C0;
        }
        QScrollBar:vertical {
            width: 16px;
        }
        QScrollBar:horizontal {
            height: 16px;
        }
)");


	auto mw{new main_window()};
	mw->show();

	return app.exec();
}
