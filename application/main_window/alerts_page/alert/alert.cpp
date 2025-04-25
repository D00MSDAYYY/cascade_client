#include "alert.hpp"

alert::alert( const TYPE										type,
			  const std::string&								alert_name,
			  const std::string&								tp_str,
			  const std::string&								text,
			  const std::string&								alertist_name,
			  std::optional< const std::vector< std::string > > tags )
	: _type{ type }
	, _name{ alert_name }
	, _timepoint{ tp_str } // TODO! switch to timepoint class here
	, _text{ text }
	, _alertist_name{ alertist_name }
	, _tags{ tags.value_or( std::vector< std::string >{} ) }
{
}

void
alert::register_in_lua( const scripting::engine::ptr& ngn_ptr )
{
	if ( can_register_in_lua< alert >( ngn_ptr ) )
		{
			auto	   type{ ngn_ptr->new_usertype< alert >(
				  _class_name,
				  sol::constructors< alert(
					  const TYPE,
					  const std::string&,
					  const std::string&,
					  const std::string&,
					  const std::string&,
					  std::optional< const std::vector< std::string > > ) >() ) };

			sol::table alert_type{ ngn_ptr->lua_state(), sol::create };
			type["TYPE"] = alert_type;
			alert_type [ "ALARM" ]	 = alert::TYPE::ALARM;
			alert_type [ "WARNING" ] = alert::TYPE::WARNING;
			alert_type [ "INFO" ]	 = alert::TYPE::INFO;


			// !TODO mb create getter-setter pairs ( or no coz readonly stuff should be)
			type [ "get_type" ]			 = &alert::get_type;
			type [ "get_name" ]			 = &alert::get_name;
			type [ "get_timepoint" ]	 = &alert::get_timepoint;
			type [ "get_text" ]			 = &alert::get_text;
			type [ "get_alertist_name" ] = &alert::get_alertist_name;
			type [ "get_tags" ]			 = &alert::get_tags;
		};
	std::cout << _class_name << "\t is registered" << std::endl;
}
