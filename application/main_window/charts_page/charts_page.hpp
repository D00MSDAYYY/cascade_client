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

	CLASS_NAME_AS_STRING(charts_page)

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



	static void
	register_in_lua( const scripting::engine::ptr& ngn_ptr );

private:
	QToolBar* _tl_bar{};
};
