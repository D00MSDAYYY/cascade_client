// #pragma once
// #include "scripting.hpp"

// #include <chrono>

// class duration
// 	: public scripting::object
// 	, public std::chrono::nanoseconds
// {
// public:
// 	using base			   = std::chrono::nanoseconds;
// 	using std_nanoseconds  = std::chrono::nanoseconds;
// 	using std_microseconds = std::chrono::microseconds;
// 	using std_milliseconds = std::chrono::milliseconds;
// 	using std_seconds	   = std::chrono::seconds;
// 	using std_minutes	   = std::chrono::minutes;
// 	using std_hours		   = std::chrono::hours;
// 	using std_days		   = std::chrono::duration< int, std::ratio< 86'400 > >;
// 	using std_weeks		   = std::chrono::duration< int, std::ratio< 604'800 > >;

// 	// Конструкторы
// 	explicit duration( const scripting::engine::ptr ngn_ptr, int64_t count = 0 )
// 		: scripting::object{ ngn_ptr }
// 		, base( count )
// 	{
// 	}

// 	explicit duration( const scripting::engine::ptr ngn_ptr, duration& ns )
// 		: scripting::object{ ngn_ptr }
// 		, base( ns )
// 	{
// 	}

// 	CLASS_NAME_AS_STRING(duration)

// 	// Фабричные методы
// 	static duration
// 	nanoseconds( int64_t count )
// 	{
// 		return duration( _ngn_ptr, std_nanoseconds( count ) );
// 	}

// 	static duration
// 	microseconds( int64_t count )
// 	{
// 		return duration( _ngn_ptr, std_microseconds( count ) );
// 	}

// 	static duration
// 	milliseconds( int64_t count )
// 	{
// 		return duration( _ngn_ptr, std_milliseconds( count ) );
// 	}

// 	static duration
// 	seconds( int64_t count )
// 	{
// 		return duration( _ngn_ptr, std_seconds( count ) );
// 	}

// 	static duration
// 	minutes( int64_t count )
// 	{
// 		return duration( _ngn_ptr, std_minutes( count ) );
// 	}

// 	static duration
// 	hours( int64_t count )
// 	{
// 		return duration( _ngn_ptr, std_hours( count ) );
// 	}

// 	static duration
// 	days( int64_t count )
// 	{
// 		return duration( _ngn_ptr, std_days( count ) );
// 	}

// 	static duration
// 	weeks( int64_t count )
// 	{
// 		return duration( _ngn_ptr, std_weeks( count ) );
// 	}

// 	// Методы получения значений
// 	int64_t
// 	get_nanoseconds() const
// 	{
// 		return count();
// 	}

// 	int64_t
// 	get_microseconds() const
// 	{
// 		return std::chrono::duration_cast< std_microseconds >( *this ).count();
// 	}

// 	int64_t
// 	get_milliseconds() const
// 	{
// 		return std::chrono::duration_cast< std_milliseconds >( *this ).count();
// 	}

// 	int64_t
// 	get_seconds() const
// 	{
// 		return std::chrono::duration_cast< std_seconds >( *this ).count();
// 	}

// 	int64_t
// 	get_minutes() const
// 	{
// 		return std::chrono::duration_cast< std_minutes >( *this ).count();
// 	}

// 	int64_t
// 	get_hours() const
// 	{
// 		return std::chrono::duration_cast< std_hours >( *this ).count();
// 	}

// 	int64_t
// 	get_days() const
// 	{
// 		return std::chrono::duration_cast< std_days >( *this ).count();
// 	}

// 	int64_t
// 	get_weeks() const
// 	{
// 		return std::chrono::duration_cast< std_weeks >( *this ).count();
// 	}

// 	// Арифметические операции
// 	duration
// 	operator+ ( const duration& other ) const
// 	{
// 		return duration( *this + other );
// 	}

// 	duration
// 	operator- ( const duration& other ) const
// 	{
// 		return duration( *this - other );
// 	}

// 	duration
// 	operator* ( int64_t factor ) const
// 	{
// 		return duration( *this * factor );
// 	}

// 	duration
// 	operator/ ( int64_t divisor ) const
// 	{
// 		return duration( *this / divisor );
// 	}

// 	// Операции сравнения
// 	bool
// 	operator== ( const duration& other ) const
// 	{
// 		return *this == other;
// 	}

// 	bool
// 	operator< ( const duration& other ) const
// 	{
// 		return *this < other;
// 	}

// 	bool
// 	operator<= ( const duration& other ) const
// 	{
// 		return *this <= other;
// 	}

// 	// Преобразование в строку
// 	std::string
// 	toString() const
// 	{
// 		if ( get_weeks() != 0 ) return std::to_string( get_weeks() ) + " weeks";
// 		if ( get_days() != 0 ) return std::to_string( get_days() ) + " days";
// 		if ( get_hours() != 0 ) return std::to_string( get_hours() ) + " hours";
// 		if ( get_minutes() != 0 ) return std::to_string( get_minutes() ) + " minutes";
// 		if ( get_seconds() != 0 ) return std::to_string( get_seconds() ) + " seconds";
// 		if ( get_milliseconds() != 0 )
// 			return std::to_string( get_milliseconds() ) + " ms";
// 		if ( get_microseconds() != 0 )
// 			return std::to_string( get_microseconds() ) + " μs";
// 		return std::to_string( get_nanoseconds() ) + " ns";
// 	}


// protected:
// 	void
// 	register_in_lua() override
// 	{
// 		if ( can_register_in_lua() )
// 			{
// 				auto ns
// 					= _ngn_ptr->globals() [ "nanoseconds" ].get_or_create< sol::table >();
// 				auto us = _ngn_ptr->globals() [ "microseconds" ]
// 							  .get_or_create< sol::table >();
// 				auto ms = _ngn_ptr->globals() [ "milliseconds" ]
// 							  .get_or_create< sol::table >();
// 				auto s = _ngn_ptr->globals() [ "seconds" ].get_or_create< sol::table >();
// 				auto m = _ngn_ptr->globals() [ "minutes" ].get_or_create< sol::table >();
// 				auto h = _ngn_ptr->globals() [ "hours" ].get_or_create< sol::table >();
// 				auto d = _ngn_ptr->globals() [ "days" ].get_or_create< sol::table >();
// 				auto w = _ngn_ptr->globals() [ "weeks" ].get_or_create< sol::table >();

// 				lua.new_usertype< duration >(
// 					class_name(),

// 					"nanoseconds",
// 					&duration::nanoseconds,
// 					"microseconds",
// 					&duration::microseconds,
// 					"milliseconds",
// 					&duration::milliseconds,
// 					"seconds",
// 					&duration::seconds,
// 					"minutes",
// 					&duration::minutes,
// 					"hours",
// 					&duration::hours,
// 					"days",
// 					&duration::days,
// 					"weeks",
// 					&duration::weeks,

// 					"get_nanoseconds",
// 					&duration::get_nanoseconds,
// 					"get_microseconds",
// 					&duration::get_microseconds,
// 					"get_milliseconds",
// 					&duration::get_milliseconds,
// 					"get_seconds",
// 					&duration::get_seconds,
// 					"get_minutes",
// 					&duration::get_minutes,
// 					"get_hours",
// 					&duration::get_hours,
// 					"get_days",
// 					&duration::get_days,
// 					"get_weeks",
// 					&duration::get_weeks,

// 					sol::meta_function::addition,
// 					&duration::operator+,
// 					sol::meta_function::subtraction,
// 					&duration::operator-,
// 					sol::meta_function::multiplication,
// 					sol::overload( []( const duration& d, int64_t f ) { return d * f; },
// 								   []( int64_t f, const duration& d ) { return d * f; } ),
// 					sol::meta_function::division,
// 					&duration::operator/,

// 					sol::meta_function::equal_to,
// 					&duration::operator==,
// 					sol::meta_function::less_than,
// 					&duration::operator<,
// 					sol::meta_function::less_than_or_equal_to,
// 					&duration::operator<=,

// 					sol::meta_function::to_string,
// 					&duration::toString );

// 				ns [ "new" ] = &duration::nanoseconds;
// 				us [ "new" ] = &duration::microseconds;
// 				ms [ "new" ] = &duration::milliseconds;
// 				s [ "new" ]	 = &duration::seconds;
// 				m [ "new" ]	 = &duration::minutes;
// 				h [ "new" ]	 = &duration::hours;
// 				d [ "new" ]	 = &duration::days;
// 				w [ "new" ]	 = &duration::weeks;
// 			}
// 	}
// };
