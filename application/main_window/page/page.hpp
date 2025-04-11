#pragma once

#include "script_engine.hpp"
#include "script_object.hpp"

#include <QMainWindow>

enum class WORKING_STATE
{
	ON,
	OFF,
	SUSPENDED
};

class page
	: public QMainWindow
	, public script::object
{
	Q_OBJECT

public:
	page( const std::string&  name,
		  script::engine::ptr ngn_ptr,
		  QWidget*			  parent = nullptr )
		: QMainWindow( parent )
		, script::object{ name, ngn_ptr } { };
	~page() { };

	void
	on()
	{
		if ( _wrkng_state != WORKING_STATE::OFF )
			{
				std::cout << "page already turned on or suspended" << std::endl;
				return;
			}
		_wrkng_state = WORKING_STATE::ON;
		on_on();
	};

	void
	off()
	{
		if ( _wrkng_state == WORKING_STATE::OFF )
			{
				std::cout << "page already turned off" << std::endl;
				return;
			}
		_wrkng_state = WORKING_STATE::OFF;
		on_off(); // Освобождение ресурсов
	};

	void
	suspend()
	{
		if ( _wrkng_state != WORKING_STATE::ON )
			{
				std::cout << "can't suspend, page is off" << std::endl;
				return;
			}
		_wrkng_state = WORKING_STATE::SUSPENDED;
		on_suspend(); // Приостановка операций
	};

	void
	resume()
	{
		if ( _wrkng_state != WORKING_STATE::SUSPENDED )
			{
				std::cout << "can't resume, page is not suspended";
				return;
			}
		_wrkng_state = WORKING_STATE::SUSPENDED;
		on_resume(); // Возобновление операций
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
	on_on() { };
	virtual void
	on_off() { };
	virtual void
	on_resume() { };
	virtual void
	on_suspend() { };


private:
	WORKING_STATE _wrkng_state{ WORKING_STATE::OFF };
};


