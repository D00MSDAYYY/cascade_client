#pragma once

#include <QGridLayout>
#include <QMainWindow>
#include <QScrollArea>
#include <QToolBar>

class scenarios_page : public QMainWindow
{
	Q_OBJECT

public:
	scenarios_page( QWidget* parent = nullptr );
	~scenarios_page() { };

private:
	QToolBar* _tl_bar{};
};
