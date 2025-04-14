#pragma once

#include "scripting.hpp"

class alert : public scripting::object
{
public:
	alert( const std::string&	  name,
		   scripting::engine::ptr ngn_ptr);
	~alert() = default;

	const std::string
	class_name() const override
	{
		return "alert";
	}

	sol::object
	make_lua_object_from_this() const override;

	void
	set_timestamp();
	void		//! what timestamp?
	get_timestamp();

	void
	set_text( const std::string& content_str );
	std::string //! json str?
	get_text();

	void		// !
	set_alertist();
	void		// !
	get_alertist();

protected:
	virtual void
	self_register() override;

private:
	std::string _text;
	// timestamp
	// alertist sol::object
};
