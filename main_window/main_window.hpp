#pragma once

#include <QMainWindow>
#include <QStackedWidget>
#include <QToolBar>

class main_window : public QMainWindow
{
	Q_OBJECT

public:
	main_window(QWidget* parent = nullptr);
	~main_window();

private:
	QToolBar* _tb{new QToolBar{"Tool bar",this}};
	QStackedWidget* _sw{new QStackedWidget{this}};
};
