#include "scripting.hpp"

#include <chrono>
#include <format>
#include <iomanip>
#include <optional>

// ! keep this class or try register std::chrono::clock::time_point for making
// available handy time operations

class timepoint
	: public scripting::object
	, public std::chrono::system_clock::time_point
{
public:
	timepoint( std::chrono::system_clock::time_point tp )
		: scripting::object{}
		, _timepoint{ tp }
	{
	}

	timepoint( timepoint&& other ) = default;

	std::string
	to_string() const;

	CLASS_NAME_AS_STRING( timepoint )

	static void
	register_in_lua( const scripting::engine::ptr& ngn_ptr );

private:
	std::chrono::system_clock::time_point _timepoint;
};
