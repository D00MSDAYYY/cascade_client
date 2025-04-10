#include "settings_page.hpp"

settings_page::settings_page( const std::string&  name,
							  script::engine::ptr ngn_ptr,
							  QWidget*			  parent )
	: page{name, ngn_ptr, parent}
{
	self_register();
}

sol::object
settings_page::create_lua_object_from_this() const
{
	return sol::make_object( _ngn_ptr->lua_state(), this );
}

void
settings_page::self_register()
{
	if ( can_self_register() )
		{
			auto type{ _ngn_ptr->new_usertype< settings_page >(
				class_name(),
				sol::base_classes,
				sol::bases< page >() ) };
		}
}
