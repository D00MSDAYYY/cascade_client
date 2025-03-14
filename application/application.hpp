#pragma once

// #include "main_window.hpp"
// #include "script_engine.hpp"

#include <QApplication>

class script_engine;
class main_window;

class application : public QApplication
{
	Q_OBJECT

public:
	application( int& argc, char** argv );
	~application() { };

private:
	std::shared_ptr< script_engine > _scrpt_ngn{};
	std::shared_ptr< main_window >	 _mn_wndw{};

	// TODO ! add terminal to app (subclass qapp)
};

