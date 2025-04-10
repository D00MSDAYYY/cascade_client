#pragma once

#include "page.hpp"
#include <QToolBar>

class charts_page
	: public page
{
	Q_OBJECT

public:
	charts_page( const std::string&	 name,
				 script::engine::ptr ngn_ptr,
				 QWidget*			 parent = nullptr );
	~charts_page() ;

	const std::string
	class_name() const override
	{
		return "charts_page";
	}

	sol::object create_lua_object_from_this() const override;

protected:
	virtual void
	self_register() override;

private:

	QToolBar*	 _tl_bar{};
};
