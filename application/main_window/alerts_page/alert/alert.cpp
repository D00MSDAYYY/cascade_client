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
	self_register();
}

void
alert::self_register()
{
	if ( can_self_register() )
		{
			// TODO! create some common _ngn_ptr and bind it with factory function

			auto factory_func{ [ ngn = this->_ngn_ptr ]( // TODO! do something with common _ngn_ptr for ALL alerts
								   const TYPE type,
								   const std::string& alert_name,
								   const std::string& tp_str,
								   const std::string& text,
								   const std::string& alertist_name,
								   std::optional< const std::vector< std::string > > tags
								   = std::nullopt ) -> alert {
				return alert{ ngn,
							  type,
							  alert_name,
							  tp_str,
							  text,
							  alertist_name,
							  tags.value_or( std::vector< std::string >{} ) };
			} };


			auto type{ _ngn_ptr->new_usertype< alert >( class_name(),
														sol::call_constructor, factory_func)};
			// !TODO mb create getter-setter pairs ( or no coz readonly stuff should be)
			type [ "get_type" ]			 = &alert::get_type;
			type [ "get_name" ]			 = &alert::get_name;
			type [ "get_timepoint" ]	 = &alert::get_timepoint;
			type [ "get_text" ]			 = &alert::get_text;
			type [ "get_alertist_name" ] = &alert::get_alertist_name;
			type [ "get_tags" ]			 = &alert::get_tags;
		}
}
