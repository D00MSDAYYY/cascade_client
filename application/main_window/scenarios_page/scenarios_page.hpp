#pragma once

#include "page.hpp"


#include <QGridLayout>
#include <QScrollArea>
#include <QToolBar>

class scenarios_page
	: public page
{
	Q_OBJECT

public:
	scenarios_page( const std::string&	name,
					script::engine::ptr ngn_ptr,
					QWidget*			parent = nullptr );
	~scenarios_page() ;

	const std::string
	class_name() const override
	{
		return "scenarios_page";
	}

	sol::object
	create_lua_object_from_this() const override;

protected:
	virtual void
	self_register() override;

private:
	QToolBar* _tl_bar{};
};
