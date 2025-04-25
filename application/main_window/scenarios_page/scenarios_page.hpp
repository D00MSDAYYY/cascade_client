#pragma once

#include "page.hpp"

#include <QToolBar>

class scenarios_page
	: public page
{
	Q_OBJECT

public:
	scenarios_page( const std::string&	name,
					scripting::engine::ptr ngn_ptr,
					QWidget*			parent = nullptr );
	~scenarios_page() ;

	CLASS_NAME_AS_STRING(scenarios_page)
	MAKE_LUA_OBJECT_FROM_THIS()
	STATIC_REGISTER_IN_LUA()

	void add_scenario();
	void remove_scenario();

private:
};
