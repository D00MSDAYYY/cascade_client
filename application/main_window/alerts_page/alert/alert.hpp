#pragma once

#include "clock.hpp"
#include "scripting.hpp"

class alert : public scripting::object
{
public:
	enum class TYPE
	{
		ALARM,
		WARNING
	};

	alert( const std::string&			name,
		   const scripting::engine::ptr ngn_ptr,
		   const TYPE					type,
		   const std::string&			tp_str,
		   const std::string&			text,
		   const std::string&			alertist_name );
	~alert() = default;

	const std::string
	class_name() const override
	{
		return "alert";
	}

	std::optional< std::string >
	get_timestamp()
	{
		if ( _timepoint ) { return timepoint_to_string( *_timepoint ); }
		else { return std::nullopt; }
	}

	const std::string
	get_text()
	{
		return _text;
	}

	const std::string
	get_alertist_name()
	{
		return _alertist_name;
	}

protected:
	virtual void
	self_register() override;

private:
	TYPE											   _type;
	std::optional< std::chrono::system_clock::time_point > _timepoint;
	std::string											   _text;
	std::string											   _alertist_name;
};
