#pragma once

#include "actions_tree.hpp"
#include "page.hpp"
#include "scripting.hpp"

#include <QMainWindow>
#include <QStackedWidget>
#include <QToolBar>
#include <map>

class main_window
	: public QMainWindow
	, public scripting::object
{
	Q_OBJECT

public:
	main_window( const scripting::engine::ptr ngn_ptr, QWidget* parent = nullptr );
	~main_window();

	CLASS_NAME_AS_STRING( main_window )
	STATIC_REGISTER_IN_LUA()

	// /////////////////////////////////////////////////////////////////

	std::map< std::string, sol::object >
	get_pages();
	void
	add_page( page* page );
	void
	remove_page( page* page );
	void
	set_current_page( page* page );
	// /////////////////////////////////////////////////////////////////

private:
	struct _pg_data
	{
		page* _page_ptr;
	};

	using _nd_t = actions_tree::node< _pg_data >;


	QToolBar*					   _tl_bar{};
	QStackedWidget*				   _stkd_wdgt{};

	std::shared_ptr< _nd_t >	   _pages_tree_root{};

	std::map< std::string, page* > _pages;
};

