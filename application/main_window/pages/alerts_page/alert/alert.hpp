#pragma once

#include "scripting.hpp"
#include "timepoint.hpp"

class alert : public scripting::object
{
public:
	enum class TYPE
	{
		ALARM,
		WARNING,
		INFO
	};

	alert( const TYPE										 type,
		   const std::string&								 alert_name,
		   const std::string&								 tp_str,
		   const std::string&								 text,
		   const std::string&								 alertist_name,
		   std::optional< const std::vector< std::string > > tags = std::nullopt );

	~alert() = default;

	CLASS_NAME_AS_STRING( alert )
	MAKE_LUA_OBJECT_FROM_THIS()
	STATIC_REGISTER_IN_LUA()

	auto
	get_type() const
	{
		return _type;
	}

	auto
	get_timepoint() const
	{
		return _timepoint;
	}

	auto
	get_text() const
	{
		return _text;
	}

	auto
	get_name() const
	{
		return _name;
	}

	auto
	get_alertist_name() const
	{
		return _alertist_name;
	}

	auto
	get_tags() const
	{
		return _tags;
	}

	bool
	operator== ( const alert& a ) const
	{
		return _name == a._name
		   and _alertist_name == a._alertist_name; // TODO! mb change in the future
	}

private:
	const std::string				 _name;
	const TYPE						 _type;
	const std::string				 _timepoint;
	const std::string				 _text;
	const std::string				 _alertist_name;
	const std::vector< std::string > _tags;		   // like 'temperature', 'air', 'co2'
};
