#pragma once

#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QToolBar>
#include <QVBoxLayout>

class sensors_page : public QMainWindow
{
	Q_OBJECT

public:
	sensors_page(QWidget* parent = nullptr);
	~sensors_page() {};

	void
	addWidget();
	void
	removeWidget();

private:
	QGridLayout* _snsrs_grd{new QGridLayout{this}};
	QWidget*	 _snsrs_pln{new QWidget{this}};

	QScrollArea* _scrl_area{new QScrollArea{this}};

	QToolBar*	 _tl_bar{
		   new QToolBar{"Tool bar", this}
	 };

	// QVBoxLayout* _pg_lyt{new QVBoxLayout{this}};
};
