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

	const std::string
	class_name() const override
	{
		return "main_window";
	}

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


protected:
	void
	self_register() override;

private:
	struct _pg_d_t
	{
		page* _page_ptr;
	};

	using _nd_t = actions_tree::node< _pg_d_t >;

	QToolBar*					   _tl_bar{};
	QStackedWidget*				   _stkd_wdgt{};

	std::shared_ptr< _nd_t >	   _pages_tree_root{};

	std::map< std::string, page* > _pages;
};


