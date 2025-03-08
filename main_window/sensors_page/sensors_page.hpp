#pragma once

#include <QGridLayout>
#include <QMainWindow>
#include <QScrollArea>
#include <QToolBar>
#include <QWidget>

class sensors_page : public QMainWindow
{
	Q_OBJECT

public:
	sensors_page( QWidget* parent = nullptr );
	~sensors_page() { };

	void addSensor();
	void removeSensor();

private:
	void		 _redistributeWidgets();
	QGridLayout* _snsrs_grd{ new QGridLayout{} };
	QWidget*	 _snsrs_pln{ new QWidget{ this } };

	QScrollArea* _scrl_area{ new QScrollArea{ this } };

	QToolBar*	 _tl_bar{
		   new QToolBar{ "Tool bar", this }
	};
};
