#pragma once

#include "page.hpp"

#include <QGridLayout>
#include <QMainWindow>
#include <QScrollArea>
#include <QToolBar>

class settings_page
	: public page
{
	Q_OBJECT

public:
	settings_page( const std::string&  name,
				  script::engine::ptr ngn_ptr,
				  QWidget*			  parent = nullptr );
	~settings_page(){} ;

	const std::string
	class_name() const override
	{
		return "settings_page";
	}

	sol::object
	create_lua_object_from_this() const override;

protected:
	virtual void
	self_register() override;

private:

};
