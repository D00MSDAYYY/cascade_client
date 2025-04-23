#include "clock.hpp"

#include <format>
#include <iomanip>


void
clock::register_in_lua( const scripting::engine::ptr& ngn_ptr )
{
	timepoint::register_in_lua( ngn_ptr );

	if ( can_register_in_lua<clock>(ngn_ptr) )
		{
			auto type{ ngn_ptr->new_usertype< clock >( _class_name ) };
			type [ "now" ] = &clock::now;
		}
	std::cout << _class_name << "\t is registered" << std::endl;
}
