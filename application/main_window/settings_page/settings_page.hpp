#pragma once

#include "page.hpp"

class settings_page : public page
{
	Q_OBJECT

public:
	settings_page( const std::string&			name,
				   const scripting::engine::ptr ngn_ptr,
				   QWidget*						parent = nullptr );
	~settings_page() = default;

	const std::string
	class_name() const override
	{
		return "settings_page";
	}

	virtual sol::object
	make_lua_object_from_this() const override
	{
		return sol::make_object( _ngn_ptr->lua_state(), this );
	};

protected:
	virtual void
	self_register() override;

private:
};
