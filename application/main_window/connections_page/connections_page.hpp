#pragma once

#include <QGridLayout>
#include <QMainWindow>
#include <QScrollArea>
#include <QToolBar>

class connections_page : public QMainWindow
{
	Q_OBJECT

public:
	connections_page( QWidget* parent = nullptr );
	~connections_page() { };

	void
	addConnection();
	void
	removeConnection();

private:
	void
				 _redistributeWidgets();
	QGridLayout* _snsrs_grd{  };
	QWidget*	 _snsrs_pln{ };

	QScrollArea* _scrl_area{  };

	QToolBar*	 _tl_bar{};
};
