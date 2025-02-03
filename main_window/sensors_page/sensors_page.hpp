#pragma once


#include <QGridLayout>
#include <QMainWindow>
#include <QPushButton>
#include <QScrollArea>
#include <QVBoxLayout>

class sensors_page : public QMainWindow
{
	Q_OBJECT

public:
	sensors_page(QWidget* parent = nullptr);
	~sensors_page() {};

	void
	addWidget();

private:
	QGridLayout* _snsrs_grd{new QGridLayout{this}};
	QWidget*	 _snsrs_pln{new QWidget{this}};

	QScrollArea* _scrl_area{new QScrollArea{this}};
	// QVBoxLayout* _pg_lyt{new QVBoxLayout{this}};
};
