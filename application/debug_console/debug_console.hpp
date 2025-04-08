#pragma once

#include "script_engine.hpp"
#include "script_object.hpp"

#include <QLineEdit>
#include <QMainWindow>
#include <QPlainTextEdit>
#include <QPointer>

class debug_console
	: public QMainWindow
	, public script::object
{
	Q_OBJECT

public:
	explicit debug_console( const std::string&	name,
							script::engine::ptr ngn_ptr,
							QWidget*			parent = nullptr );
	~debug_console() { };

	const std::string
	class_name() const override
	{
		return "debug_console";
	}

protected:
	void
	self_register() override { };

private:
	void
							   _printToOutput( const QString& text );

	QPointer< QPlainTextEdit > _output;
	QPointer< QLineEdit >	   _input;

private slots:
	void
	execute_command();
};
