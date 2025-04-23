#pragma once

#include "page.hpp"

class settings_page : public page
{
	Q_OBJECT

public:
	settings_page( const std::string&			name,
				   const scripting::engine::ptr ngn_ptr,
				   QWidget*						parent = nullptr );
	~settings_page() = default;

	CLASS_NAME_AS_STRING(settings_page)



	static void
	register_in_lua( const scripting::engine::ptr& ngn_ptr );

private:
};
