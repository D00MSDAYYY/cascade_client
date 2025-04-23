// #include "scripting.hpp"

// #include <chrono>
// #include <format>
// #include <iomanip>
// #include <optional>

// // ! keep this class or try register std::chrono::clock::time_point for making
// // available handy time operations

// class timepoint
// 	: public scripting::object
// 	, public std::chrono::system_clock::time_point
// {
// public:
// 	timepoint( const scripting::engine::ptr			 ngn_ptr,
// 			   std::chrono::system_clock::time_point tp )
// 		: scripting::object{ ngn_ptr }
// 		, _timepoint{ tp }
// 	{
// 		register_in_lua();
// 	}

// 	timepoint( timepoint&& other ) = default;

// 	std::string
// 	to_string() const;

// CLASS_NAME_AS_STRING(timepoint)

// protected:
// 	void
// 	register_in_lua() override;

// private:
	// std::chrono::system_clock::time_point _timepoint;
// };
