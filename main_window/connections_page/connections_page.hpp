#pragma once

#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QToolBar>
#include <QVBoxLayout>

class connections_page : public QMainWindow
{
	Q_OBJECT

public:
	connections_page(QWidget* parent = nullptr);
	~connections_page() {};

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
