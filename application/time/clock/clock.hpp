#include "scripting.hpp"

#include <chrono>
#include <format>
#include <iomanip>
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

	timepoint
	now()
	{
		return timepoint{ _ngn_ptr, std::chrono::system_clock::now() };
	}

protected:
	void
	register_in_lua() override
	;
};


