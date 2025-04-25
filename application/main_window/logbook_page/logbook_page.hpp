#pragma once

#include "page.hpp"

class logbook_page : public page
{
	Q_OBJECT

public:
	logbook_page( const std::string&		   name,
				  const scripting::engine::ptr ngn_ptr,
				  QWidget*					   parent = nullptr );
	~logbook_page();

	CLASS_NAME_AS_STRING( lobbook_page )
	MAKE_LUA_OBJECT_FROM_THIS()
	STATIC_REGISTER_IN_LUA()

	void
	add_log( const std::string& log ); //! TODO mb change to special log class
private:
	;
};
