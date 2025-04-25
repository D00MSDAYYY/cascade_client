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

	CLASS_NAME_AS_STRING( timepoint )
	STATIC_REGISTER_IN_LUA()

	std::string
	to_string() const;

private:
	std::chrono::system_clock::time_point _timepoint;
};
