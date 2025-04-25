#pragma once

#include "actions_tree.hpp"
#include "scripting.hpp"

#include <QMainWindow>
#include <QToolBar>

class page
	: public QMainWindow
	, public scripting::object
{
	Q_OBJECT

public:
	page( const std::string&		   name,
		  const scripting::engine::ptr ngn_ptr,
		  QWidget*					   parent = nullptr )
		: QMainWindow( parent )
		, scripting::object{ ngn_ptr }
		, _name{ name }
	{
		_tl_bar = new QToolBar( "Toolbar" );
		addToolBar( Qt::TopToolBarArea, _tl_bar );
		_tl_bar->setIconSize( { 32, 32 } );
		_tl_bar->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
		_tl_bar->setMovable( false );
		_tl_bar->addWidget(new QWidget{this});
	};

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

	WORKING_STATE
	get_state() const { return _wrkng_state; };

	std::string
	get_report() const
	{
		return "default empty report";
	}

	const std::string _name;

protected:
	virtual void
	on_on() { };
	virtual void
	on_off() { };
	virtual void
	on_resume() { };
	virtual void
	on_suspend() { };

	struct _c_c_d_t
	{
		QAction*	_qaction{};
		std::string _script{};
	};

	using _nd_t = actions_tree::node< _c_c_d_t >;

	std::shared_ptr< _nd_t > _actions_tree_root{};
	QToolBar*				 _tl_bar{};

private:
	WORKING_STATE _wrkng_state{ WORKING_STATE::OFF };
};


