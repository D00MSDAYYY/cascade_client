#pragma once

#include "clock.hpp"
#include "scripting.hpp"

class alert : public scripting::object
{
public:
	enum class TYPE
	{
		ALARM,
		WARNING,
		INFO
	};

	alert( const scripting::engine::ptr		ngn_ptr,
		   const TYPE						type,
		   const std::string&				alert_name,
		   const std::string&				tp_str,
		   const std::string&				text,
		   const std::string&				alertist_name,
		   const std::vector< std::string > tags = {} );
	~alert() = default;

	const std::string
	class_name() const override
	{
		return "alert";
	}

	auto
	get_type()
	{
		return _type;
	}

	auto
	get_timepoint()
	{
		return _timepoint;
	}

	auto
	get_text()
	{
		return _text;
	}

	auto
	get_name()
	{
		return _alert_name;
	}

	auto
	get_alertist_name()
	{
		return _alertist_name;
	}

	auto
	get_tags()
	{
		return _tags;
	}

protected:
	virtual void
	self_register() override;

private:
	const std::string				 _alert_name;
	const TYPE						 _type;
	const std::string				 _timepoint;
	const std::string				 _text;
	const std::string				 _alertist_name;
	const std::vector< std::string > _tags; // like 'temperature', 'air', 'co2'
};
