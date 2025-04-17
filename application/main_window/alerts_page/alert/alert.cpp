#include "alert.hpp"

alert::alert( const std::string&		   name,
			  const scripting::engine::ptr ngn_ptr,
			  const TYPE				   type,
			  const std::string&		   tp_str,
			  const std::string&		   text,
			  const std::string&		   alertist_name )
	: scripting::object{ name, ngn_ptr }
	, _type{ type }
	, _timepoint{ string_to_timepoint( tp_str ) }
	, _text{ text }
	, _alertist_name{ alertist_name }
{
}

void
alert::self_register()
{
	if ( can_self_register() )
		{
			auto type{ _ngn_ptr->new_usertype< alert >( class_name() ) };
			type [ "get_timestamp" ]	 = &alert::get_timestamp;
			type [ "get_text" ]			 = &alert::get_text;
			type [ "get_alertist_name" ] = &alert::get_alertist_name;

			_ngn_ptr->new_enum< TYPE >( "ALERT_TYPE",
										{
										  { "ALARM",	 TYPE::ALARM	 },
										  { "WARNING", TYPE::WARNING }
			   } );
		}
}
