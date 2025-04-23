#include "settings_page.hpp"

settings_page::settings_page( const std::string&  name,
							  const scripting::engine::ptr ngn_ptr,
							  QWidget*			  parent )
	: page{name, ngn_ptr, parent}
{
	register_in_lua(*_ngn_ptr);
}



void
settings_page::register_in_lua(const scripting::engine::ptr& ngn_ptr)
{
	if ( can_register_in_lua<settings_page>(ngn_ptr) )
		{
			auto type{ ngn_ptr->new_usertype< settings_page >(
			_class_name,
				sol::base_classes,
				sol::bases< page >() ) };
		}
}
