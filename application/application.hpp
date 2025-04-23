#pragma once

#include "clock.hpp"
#include "debug_console.hpp"
#include "main_window.hpp"
#include "scripting.hpp"

#include <QApplication>

class main_window;

class application
	: public QApplication
	, public scripting::object
{
	Q_OBJECT

public:
	application( int& argc, char** argv );
	~application() = default;

	CLASS_NAME_AS_STRING(application)

	static void
	register_in_lua( const scripting::engine::ptr& ngn_ptr );

private:
	std::shared_ptr< main_window >	 _mn_wndw{};
	std::shared_ptr< debug_console > _dbg_wndw{};
	std::shared_ptr< class clock >		 _clock{};
};

