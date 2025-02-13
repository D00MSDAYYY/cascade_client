#pragma once

#include <QGridLayout>
#include <QMainWindow>
#include <QScrollArea>
#include <QToolBar>

class logbook_page : public QMainWindow
{
	Q_OBJECT

public:
	logbook_page(QWidget* parent = nullptr);
	~logbook_page() {};

	void
	addConnection();
	void
	removeConnection();

private:
	void
				 _redistributeWidgets();
	QGridLayout* _snsrs_grd{new QGridLayout{}};
	QWidget*	 _snsrs_pln{new QWidget{this}};

	QScrollArea* _scrl_area{new QScrollArea{this}};

	QToolBar*	 _tl_bar{
		   new QToolBar{"Tool bar", this}
	 };
};
