#include "clock.hpp"

// std::optional< std::chrono::system_clock::time_point >
// string_to_timepoint( const std::string& str )
// {
// 	std::tm			   tm = {};
// 	std::istringstream ss( str );
// 	ss >> std::get_time( &tm, "%Y-%m-%d %H:%M:%S" );

// 	if ( ss.fail() ) return std::nullopt;

// 	std::time_t time = std::mktime( &tm );
// 	return std::chrono::system_clock::from_time_t( time );
// }

std::optional< std::string >
timepoint::timepoint_to_string(  ) const
{
	try
		{
			auto str{ std::format( "%Y-%m-%d %H:%M:%S", _timepoint ) };
			return str;
		}
	catch ( const std::exception& e )
		{
			return std::nullopt;
		}
}

void
timepoint::self_register()
{
}
