#pragma once

#include <QGridLayout>
#include <QMainWindow>
#include <QScrollArea>
#include <QToolBar>

class logbook_page : public QMainWindow
{
	Q_OBJECT

public:
	logbook_page( QWidget* parent = nullptr );
	~logbook_page() { };

private:
	;
};
