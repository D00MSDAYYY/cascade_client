#pragma once

#include "script_engine.hpp"
#include "script_object.hpp"

#include <QGridLayout>
#include <QMainWindow>
#include <QScrollArea>
#include <QToolBar>

class settings_page
	: public QMainWindow
	, public script::object
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

protected:
	virtual void
	self_register() override{};

private:

};
