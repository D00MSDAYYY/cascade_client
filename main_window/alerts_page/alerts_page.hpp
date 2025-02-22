#pragma once

#include <QGridLayout>
#include <QMainWindow>
#include <QScrollArea>
#include <QToolBar>

class alerts_page : public QMainWindow
{
	Q_OBJECT

public:
	alerts_page(QWidget* parent = nullptr);
	~alerts_page() {};
private:
	QScrollArea* _scrl_area{new QScrollArea{this}};
	QToolBar*	 _tl_bar{
		   new QToolBar{"Tool bar", this}
	 };
};
