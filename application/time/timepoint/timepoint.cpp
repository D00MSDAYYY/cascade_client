#include "timepoint.hpp"

std::string
timepoint::to_string() const
{
	auto			   tt = std::chrono::system_clock::to_time_t( _timepoint );
	auto			   tm = *std::localtime( &tt );

	std::ostringstream oss;
	oss << std::put_time( &tm, "%Y-%m-%d %H:%M:%S" );
	return oss.str();
}

void
timepoint::register_in_lua( const scripting::engine::ptr& ngn_ptr )
{
	if ( can_register_in_lua<timepoint>(ngn_ptr) )
		{
			auto type = ngn_ptr->new_usertype< timepoint >(
				_class_name,
				sol::meta_function::addition,
				sol::overload(
					[]( const timepoint& tp, std::chrono::seconds sec ) {
						return timepoint(  tp._timepoint + sec );
					},
					[]( const timepoint& tp, std::chrono::minutes min ) {
						return timepoint(  tp._timepoint + min );
					},
					[]( const timepoint& tp, std::chrono::hours hrs ) {
						return timepoint(  tp._timepoint + hrs );
					},
					[]( const timepoint& tp, const timepoint& other ) {
						return tp._timepoint + other._timepoint.time_since_epoch();
					} ),
				sol::meta_function::subtraction,
				sol::overload(
					[]( const timepoint& tp, std::chrono::seconds sec ) {
						return timepoint(  tp._timepoint - sec );
					},
					[]( const timepoint& tp, std::chrono::minutes min ) {
						return timepoint(  tp._timepoint - min );
					},
					[]( const timepoint& tp, std::chrono::hours hrs ) {
						return timepoint(  tp._timepoint - hrs );
					},
					[]( const timepoint& tp, const timepoint& other ) {
						return tp._timepoint - other._timepoint; //! TODO
					} ),
				sol::meta_function::equal_to,
				[]( const timepoint& a, const timepoint& b ) {
					return a._timepoint == b._timepoint;
				},
				sol::meta_function::less_than,
				[]( const timepoint& a, const timepoint& b ) {
					return a._timepoint < b._timepoint;
				},
				sol::meta_function::to_string,
				&timepoint::to_string );
			// todo add this funcs into appropriate table


			// Методы для получения компонентов времени
			type [ "get_seconds" ] = []( timepoint& self ) {
				auto tt = std::chrono::system_clock::to_time_t( self._timepoint );
				auto tm = *std::localtime( &tt );
				return tm.tm_sec;
			};

			type [ "get_minutes" ] = []( timepoint& self ) {
				auto tt = std::chrono::system_clock::to_time_t( self._timepoint );
				auto tm = *std::localtime( &tt );
				return tm.tm_min;
			};

			type [ "get_hours" ] = []( timepoint& self ) {
				auto tt = std::chrono::system_clock::to_time_t( self._timepoint );
				auto tm = *std::localtime( &tt );
				return tm.tm_hour;
			};

			type [ "get_day" ] = []( timepoint& self ) {
				auto tt = std::chrono::system_clock::to_time_t( self._timepoint );
				auto tm = *std::localtime( &tt );
				return tm.tm_mday;
			};

			type [ "get_month" ] = []( timepoint& self ) {
				auto tt = std::chrono::system_clock::to_time_t( self._timepoint );
				auto tm = *std::localtime( &tt );
				return tm.tm_mon + 1; // 0-11 -> 1-12
			};

			type [ "get_year" ] = []( timepoint& self ) {
				auto tt = std::chrono::system_clock::to_time_t( self._timepoint );
				auto tm = *std::localtime( &tt );
				return tm.tm_year + 1'900;
			};
		}
	std::cout << _class_name << "\t is registered" << std::endl;
}
