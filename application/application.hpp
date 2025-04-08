#pragma once

#include "debug_console.hpp"
#include "main_window.hpp"
#include "script_engine.hpp"
#include "script_object.hpp"

#include <QApplication>

class main_window;

class application
	: public QApplication
	, public script::object
{
	Q_OBJECT

public:
	application( int& argc, char** argv );
	~application() { };

protected:
	void
	self_register() override;

private:
	std::shared_ptr< main_window >	 _mn_wndw{};
	std::shared_ptr< debug_console > _dbg_wndw{};
};

