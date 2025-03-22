#pragma once

// #include "script_engine.hpp"

#include <QMainWindow>
#include <QStackedWidget>
#include <QToolBar>
#include <memory>

class main_window : public QMainWindow
{
	Q_OBJECT

public:
	main_window( QWidget* parent = nullptr );
	~main_window();

private:
	QToolBar*		_tl_bar{};
	QStackedWidget* _stkd_wgt{};
};

