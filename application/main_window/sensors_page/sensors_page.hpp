#pragma once

#include "page.hpp"

#include <QGridLayout>
#include <QScrollArea>
#include <QToolBar>

class sensors_page
	: public page
{
	Q_OBJECT

public:
	sensors_page( const std::string&  name,
				  script::engine::ptr ngn_ptr,
				  QWidget*			  parent = nullptr );
	~sensors_page() ;

	void
	addSensor();
	void
	removeSensor();

	const std::string
	class_name() const override
	{
		return "sensors_page";
	}

	sol::object
	create_lua_object_from_this() const override;

protected:
	virtual void
	self_register() override;

private:
	void
				 _redistributeWidgets();
	QGridLayout* _snsrs_grd{};
	QWidget*	 _snsrs_pln{};

	QScrollArea* _scrl_area{};

	QToolBar*	 _tl_bar{};
};
