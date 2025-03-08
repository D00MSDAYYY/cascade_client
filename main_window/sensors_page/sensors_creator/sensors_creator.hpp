#pragma once

#include <QBoxLayout>
#include <QComboBox>
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class sensors_creator : public QDialog
{
	Q_OBJECT

public:
	sensors_creator( QWidget* parent = 0 );
	~sensors_creator() { };

signals:
	void sensorCreated( QWidget* sensor );

private:
	;
};
