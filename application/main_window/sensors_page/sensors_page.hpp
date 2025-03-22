#pragma once
#include "script_engine.hpp"

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

	void
	addSensor();
	void
	removeSensor();

private:
	void
				 _redistributeWidgets();
	QGridLayout* _snsrs_grd{};
	QWidget*	 _snsrs_pln{};

	QScrollArea* _scrl_area{};

	QToolBar*	 _tl_bar{};
};
