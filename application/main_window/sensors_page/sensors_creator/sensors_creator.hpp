#pragma once

#include "scripting.hpp"
#include "sensor.hpp"

#include <QWidget>

class sensors_creator
	: public QWidget
	, public scripting::object
{
	Q_OBJECT

public:
	sensors_creator( const scripting::engine::ptr ngn_ptr, QWidget* parent = 0 );
	~sensors_creator();

signals:
	void
	sensor_created( std::shared_ptr< sensor > sensor_ptr );
};
