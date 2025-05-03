#pragma once

#include "actions_tree.hpp"
#include "scripting.hpp"

#include <QMainWindow>
#include <QMenu>
#include <QToolBar>
#include <QToolButton>
#include "sensor.hpp"

class page
	: public QMainWindow
	, public scripting::object
{
	Q_OBJECT

public:
	page( const std::string&		   name,
		  const scripting::engine::ptr ngn_ptr,
		  QWidget*					   parent = nullptr );

	~page() = default;

	enum class WORKING_STATE
	{
		ON,
		OFF,
		SUSPENDED
	};

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
		on_off();
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
		on_suspend();
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
		on_resume();
	};

	auto
	get_name() const
	{
		return _name;
	}

	WORKING_STATE
	get_state() const { return _wrkng_state; };

	std::string
	get_report() const
	{
		return "default empty report";
	}

	struct _qact_scr
	{
		QAction*	_qaction{};
		std::string _script{};
	};

	using _nd_t = actions_tree::node< _qact_scr >;

	static QAction*
	_bind_qaction_with_func( QAction* action, auto func )
	{
		QObject::connect( action, &QAction::triggered, [ func, action ]() {
			func( action );
		} );
		return action;
	};

protected:
	void
	_init_toolbar( _nd_t&  actions_tree_root);

	virtual void
	on_on() { };
	virtual void
	on_off() { };
	virtual void
	on_resume() {
	}

	void on_suspend() { };

	QToolBar*				 _tl_bar{};

private:
	WORKING_STATE	  _wrkng_state{ WORKING_STATE::OFF };
	const std::string _name;
};


