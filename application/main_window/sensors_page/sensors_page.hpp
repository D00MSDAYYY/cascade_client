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
				  const scripting::engine::ptr ngn_ptr,
				  QWidget*			  parent = nullptr );
	~sensors_page() ;

	CLASS_NAME_AS_STRING( sensors_page )
	MAKE_LUA_OBJECT_FROM_THIS()
	STATIC_REGISTER_IN_LUA()

	void
	addSensor();
	void
	removeSensor();



	void add_sensor();
	void remove_sensor();

private:
	void
				 _redistributeWidgets();
	QGridLayout* _snsrs_grd{};
	QWidget*	 _snsrs_pln{};

	QScrollArea* _scrl_area{};

};
