#include "scripting.hpp"

#include <chrono>

#include <optional>
#include "timepoint.hpp"
#include "duration.hpp"

class clock
	: public scripting::object
	, public std::chrono::system_clock
{
public:
	clock( const scripting::engine::ptr& ngn_ptr )
		: scripting::object( ngn_ptr )
	{
		register_in_lua(*_ngn_ptr);
		
	}

	CLASS_NAME_AS_STRING(clock)
	STATIC_REGISTER_IN_LUA()

	timepoint
	now()
	{
		return timepoint{  std::chrono::system_clock::now() };
	}

};


