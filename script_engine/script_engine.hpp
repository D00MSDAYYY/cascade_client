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
	QToolBar* _tl_bar{
		new QToolBar{"Tool bar", this}
	  };
	QStackedWidget* _stkd_wgt{new QStackedWidget{this}};
};
