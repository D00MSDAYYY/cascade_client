#pragma once

#include "scripting.hpp"
#include "sensor.hpp"
#include "actions_tree.hpp"

#include <QWidget>

class sensors_creator
	: public QWidget
	, public scripting::object //! TODO add scripting stuff in this class
{
	Q_OBJECT

public:
	sensors_creator( const scripting::engine::ptr ngn_ptr, QWidget* parent = 0 );
	~sensors_creator();

	struct _qact_scr
	{
		QAction*	_qaction{};
		std::string _script{};
	};

	using _nd_t = actions_tree::node< _qact_scr >;

signals:
	void
	sensor_created( std::shared_ptr< sensor > sensor_ptr );

};
