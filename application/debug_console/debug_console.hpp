#pragma once

#include "scripting.hpp"

#include <QLineEdit>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QPointer>

class debug_console
	: public QMainWindow
	, public scripting::object
{
	Q_OBJECT

public:
	explicit debug_console( scripting::engine::ptr ngn_ptr, QWidget* parent = nullptr );
	~debug_console() = default;

private:
	void
							   _printToOutput( const QString& text );

	QPointer< QPlainTextEdit > _output;
	QPointer< QLineEdit >	   _input;

private slots:
	void
	execute_command();
};
