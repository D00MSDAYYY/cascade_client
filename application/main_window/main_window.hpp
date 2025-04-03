#pragma once

#include "script_engine.hpp"
#include "script_object.hpp"

#include <QMainWindow>
#include <QStackedWidget>
#include <QTabWidget>
#include <QToolBar>
#include <map>

class main_window
	: public QMainWindow
	, public script::object
{
	Q_OBJECT

public:
	main_window( const std::string&	 name,
				 script::engine::ptr ngn_ptr,
				 QWidget*			 parent = nullptr );
	~main_window();

	const std::string
	class_name() override
	{
		return "main_window";
	}

	bool
	_test_fn()
	{
		std::cout << "test fn" << std::endl;
		return true;
	}

protected:
	void
	self_register() override;

private:
	QToolBar*						  _tl_bar{};
	QStackedWidget*					  _stkd_wgt{};

	// std::map< std::string, QWidget* > _pages;
	std::map< std::string, sol::object > _pages_lua_obj;
};


