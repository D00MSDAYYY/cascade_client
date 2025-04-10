#pragma once

#include "script_engine.hpp"
#include "script_object.hpp"

#include <QMainWindow>
#include <map>

class page
	: public QMainWindow
	, public script::object
{
	Q_OBJECT

public:
	page( const std::string&  name,
		  script::engine::ptr ngn_ptr,
		  QWidget*			  parent = nullptr )
		: QMainWindow( parent )
		, script::object{ name, ngn_ptr }
	{
	};

	~page() { };
};


