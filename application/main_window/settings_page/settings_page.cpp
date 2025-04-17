#include "settings_page.hpp"

settings_page::settings_page( const std::string&  name,
							  const scripting::engine::ptr ngn_ptr,
							  QWidget*			  parent )
	: page{name, ngn_ptr, parent}
{
	self_register();
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
