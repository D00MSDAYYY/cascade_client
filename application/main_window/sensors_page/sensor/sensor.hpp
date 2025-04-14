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
	sensor( const std::string&	name,
			scripting::engine::ptr ngn_ptr,
			QWidget*			parent = nullptr );
	~sensor() = default;

	const std::string
	class_name() const override
	{
		return "sensor";
	}

	sol::object
	make_lua_object_from_this() const override;

	void
	on();
	void
	off();
	void
	suspend();
	void
	resume();

	void add_widget();
	void subscribe();
	void unsubscribe();
	void update(); // ! TODO mb use qt signals?

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

protected:
	virtual void
	self_register() override;

	// !TODO mb merge 'sensor' and 'page' classes in one base class? but i have trouble
	// with dirrent parent for both (QWidget and QMainWindow)
	virtual void
	on_on() { };
	virtual void
	on_off() { };
	virtual void
	on_resume() { };
	virtual void
	on_suspend() { };

private:
	QHBoxLayout*  layout;

	WORKING_STATE _wrkng_state{ WORKING_STATE::OFF };
};
