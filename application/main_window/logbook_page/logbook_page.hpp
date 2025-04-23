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

	void
	add_log( const std::string& log ); //! TODO mb change to special log class

	static void
	register_in_lua( const scripting::engine::ptr& ngn_ptr );

private:
	;
};
