#include "alert.hpp"

alert::alert( const scripting::engine::ptr	   ngn_ptr,
			  const TYPE					   type,
			  const std::string&			   alert_name,
			  const std::string&			   tp_str,
			  const std::string&			   text,
			  const std::string&			   alertist_name,
			  const std::vector< std::string > tags )
	: scripting::object{ ngn_ptr }
	, _alert_name{ alert_name }
	, _type{ type }
	, _timepoint{ tp_str }
	, _text{ text }
	, _alertist_name{ alertist_name }
	, _tags{ tags }
{
}

void
alert::self_register()
{
	if ( can_self_register() )
		{
			auto type{ _ngn_ptr->new_usertype< alert >( class_name() ) };
			// !TODO mb create getter-setter pairs
			type [ "get_type" ]			 = &alert::get_type;
			type [ "get_name" ]			 = &alert::get_name;
			type [ "get_timepoint" ]	 = &alert::get_timepoint;
			type [ "get_text" ]			 = &alert::get_text;
			type [ "get_alertist_name" ] = &alert::get_alertist_name;
			type [ "get_tags" ]			 = &alert::get_tags;
		}
}
