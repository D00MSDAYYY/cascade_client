#pragma once

#include "scripting.hpp"

#include <QHBoxLayout>
#include <QWidget>

class sensor
	: public QWidget
	, public scripting::object
{
	Q_OBJECT

public:
	sensor( const std::string&	   name,
			scripting::engine::ptr ngn_ptr,
			QWidget*			   parent = nullptr );
	~sensor() = default;

	CLASS_NAME_AS_STRING(sensor)
	STATIC_REGISTER_IN_LUA()

	void
	on();
	void
	off();
	void
	suspend();
	void
	resume();

	void
	add_widget();
	void
	subscribe();
	void
	unsubscribe();
	void
	update(); // ! TODO mb use qt signals?

	enum class WORKING_STATE
	{
		ON,
		OFF,
		SUSPENDED
	};

	WORKING_STATE
	get_state() const { return _wrkng_state; };

	std::string
	get_report() const
	{
		return "default empty report";
	}

	virtual void
	on_on() { };
	virtual void
	on_off() { };
	virtual void
	on_resume() { };
	virtual void
	on_suspend() { };

private:
	QHBoxLayout*	  layout;

	WORKING_STATE	  _wrkng_state{ WORKING_STATE::OFF };
	const std::string _name;
};
