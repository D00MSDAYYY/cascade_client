#pragma once

#include "sensor.hpp"


#include <QWidget>

class sensors_creator : public QWidget
{
	Q_OBJECT

public:
	sensors_creator( QWidget* parent = 0 );
	~sensors_creator() ;

signals:
	void
	sensor_created( std::shared_ptr<sensor> sensor_ptr );
};
