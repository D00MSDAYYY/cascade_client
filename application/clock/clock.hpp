#include "scripting.hpp"

#include <chrono>
#include <format>
#include <iomanip>
#include <optional>

// ! keep this class or try register std::chrono::system_clock::time_point for making
// available handy time operations

class timepoint : public scripting::object
{
public:
	timepoint( const scripting::engine::ptr			 ngn_ptr,
			   std::chrono::system_clock::time_point tp )
		: scripting::object{ ngn_ptr }
		, _timepoint{ tp }
	{
	}

	timepoint( timepoint&& other ) = default;

	// static std::optional< std::chrono::system_clock::time_point >
	// string_to_timepoint( const std::string& str );

	std::optional< std::string >
	timepoint_to_string() const;

	const std::string
	class_name() const override
	{
		return "timepoint";
	}

protected:
	void
	self_register() override;

private:
	std::chrono::system_clock::time_point _timepoint;
};
