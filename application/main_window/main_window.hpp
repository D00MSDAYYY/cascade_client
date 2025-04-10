#pragma once

#include "actions_tree.hpp"
#include "page.hpp"
#include "script_engine.hpp"
#include "script_object.hpp"

#include <QMainWindow>
#include <QStackedWidget>
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
	class_name() const override
	{
		return "main_window";
	}

	sol::object
	create_lua_object_from_this() const override;

protected:
	void
	self_register() override;

private:
	struct _pg_d_t
	{
		page* _page_ptr;
	};
	using _nd_t = actions_tree::node< _pg_d_t >;

	QToolBar*							 _tl_bar{};
	QStackedWidget*						 _stkd_wdgt{};

	std::shared_ptr< _nd_t >			 _pages_tree_root{};

	std::map< std::string, sol::object > _sys_pages_lua_obj;
	std::map< std::string, sol::object > _cstm_pages_lua_obj;
};


