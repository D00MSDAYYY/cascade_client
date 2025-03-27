#pragma once

#include "main_window.hpp"
#include "script_engine.hpp"

#include <QApplication>

class main_window;

class application : public QApplication
{
	Q_OBJECT

public:
	application( int& argc, char** argv );
	~application() { };

private:
	std::shared_ptr< script::engine > _engine{};
	std::shared_ptr< main_window >	  _mn_wndw{};
};

