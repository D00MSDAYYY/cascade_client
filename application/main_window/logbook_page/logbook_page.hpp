#pragma once

#include "page.hpp"

#include <QGridLayout>
#include <QScrollArea>
#include <QToolBar>

class logbook_page
	: public page
{
	Q_OBJECT

public:
	logbook_page( const std::string&  name,
				  script::engine::ptr ngn_ptr,
				  QWidget*			  parent = nullptr );
	~logbook_page() ;

	const std::string
	class_name() const override
	{
		return "logbook_page";
	}

	sol::object
	create_lua_object_from_this() const override;

protected:
	virtual void
	self_register() override;

private:
	;
};
