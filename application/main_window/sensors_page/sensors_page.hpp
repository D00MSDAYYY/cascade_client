#pragma once

#include "script_engine.hpp"
#include "script_object.hpp"

#include <QGridLayout>
#include <QMainWindow>
#include <QScrollArea>
#include <QToolBar>
#include <QWidget>

class sensors_page
	: public QMainWindow
	, public script::object
{
	Q_OBJECT

public:
	sensors_page( const std::string&  name,
				  script::engine::ptr ngn_ptr,
				  QWidget*			  parent = nullptr );
	~sensors_page() { };

	void
	addSensor();
	void
	removeSensor();

	const std::string
	class_name() override
	{
		return "sensors_page";
	}

protected:
	virtual void
	self_register() override{};

private:
	void
				 _redistributeWidgets();
	QGridLayout* _snsrs_grd{};
	QWidget*	 _snsrs_pln{};

	QScrollArea* _scrl_area{};

	QToolBar*	 _tl_bar{};
};
