#pragma once

#include "page.hpp"

#include <QToolBar>

class charts_page : public page
{
	Q_OBJECT

public:
	charts_page( const std::string&	 name,
				 const scripting::engine::ptr ngn_ptr,
				 QWidget*			 parent = nullptr );
	~charts_page();

	const std::string
	class_name() const override
	{
		return "charts_page";
	}

	// /////////////////////////////////////////////////////////////////

	std::multimap< std::string, sol::object >
	get_charts();
	// TODO! mb add alert id as return to unique identifing (to store into alertist to
	// faster and convinient deletion)
	void
	add_chart(  ); 

	void
	remove_chart( const std::string& alert_name, const std::string& alertist_name );

	void
	sort() { };		   // TODO! implement sorting (by name, tags, type, ... )

	// /////////////////////////////////////////////////////////////////

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
