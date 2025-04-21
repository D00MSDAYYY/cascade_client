#pragma once

#include "page.hpp"

#include <QToolBar>

class scenarios_page
	: public page
{
	Q_OBJECT

public:
	scenarios_page( const std::string&	name,
					scripting::engine::ptr ngn_ptr,
					QWidget*			parent = nullptr );
	~scenarios_page() ;

	const std::string
	class_name() const override
	{
		return "scenarios_page";
	}

	void add_scenario();
	void remove_scenario();

	virtual sol::object
	make_lua_object_from_this() const override
	{
		return sol::make_object( _ngn_ptr->lua_state(), this );
	};

protected:
	virtual void
	self_register() override;

private:
	QToolBar* _tl_bar{};
};
