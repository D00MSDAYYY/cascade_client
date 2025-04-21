#pragma once

#include "page.hpp"

class logbook_page : public page
{
	Q_OBJECT

public:
	logbook_page( const std::string&  name,
				  const scripting::engine::ptr ngn_ptr,
				  QWidget*			  parent = nullptr );
	~logbook_page();

	const std::string
	class_name() const override
	{
		return "logbook_page";
	}

	void
	add_log( const std::string& log ); //! TODO mb change to special log class

	virtual sol::object
	make_lua_object_from_this() const override
	{
		return sol::make_object( _ngn_ptr->lua_state(), this );
	};

protected:
	virtual void
	self_register() override;

private:
	;
};
