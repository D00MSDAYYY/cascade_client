#pragma once

#include "clock.hpp"
#include "debug_console.hpp"
#include "main_window.hpp"
#include "scripting.hpp"

#include <QApplication>

class application
	: public QApplication
	, public scripting::object
{
	Q_OBJECT

public:
	application( int& argc, char** argv );
	~application() = default;

	CLASS_NAME_AS_STRING(application)
	STATIC_REGISTER_IN_LUA()

private:
	std::shared_ptr< main_window >	 _mn_wndw{};
	std::shared_ptr< debug_console > _dbg_wndw{};
	std::shared_ptr< class clock >		 _clock{};
};

