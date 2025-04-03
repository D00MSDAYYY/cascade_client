#pragma once

#include "script_engine.hpp"
#include "script_object.hpp"

#include <QGridLayout>
#include <QMainWindow>
#include <QScrollArea>
#include <QToolBar>

class logbook_page
	: public QMainWindow
	, public script::object
{
	Q_OBJECT

public:
	logbook_page( const std::string&  name,
				  script::engine::ptr ngn_ptr,
				  QWidget*			  parent = nullptr );
	~logbook_page() { };

	const std::string
	class_name() override
	{
		return "logbook_page";
	}

protected:
	virtual void
	self_register() override{};

private:
	;
};
