#include "debug_console.hpp"

#include <QKeyEvent>
#include <QScrollBar>
#include <QVBoxLayout>
#include <iostream>

debug_console::debug_console( const scripting::engine::ptr ngn_ptr, QWidget* parent )
	: QMainWindow{ parent }
	, scripting::object{ ngn_ptr }
{
	auto cntrl_wgt{ new QWidget{ this } };
	auto layout{ new QVBoxLayout( cntrl_wgt ) };

	_output = new QPlainTextEdit( this );
	_output->setReadOnly( true );
	_output->setWordWrapMode( QTextOption::NoWrap );

	_input = new QLineEdit( this );
	_input->setPlaceholderText( "Enter Lua command..." );

	layout->addWidget( _output );
	layout->addWidget( _input );

	connect( _input, &QLineEdit::returnPressed, this, &debug_console::execute_command );

	(*_ngn_ptr)->globals() [ "debug_output" ] = [ this ]( const std::string& text ) {
		_printToOutput( QString::fromStdString( text ) );
	};

	(*_ngn_ptr)->script( R"(
        local original_print = print
        print = function(...)
            local args = {...}
            local str = ""
            for i,v in ipairs(args) do
                if i > 1 then str = str .. "\t" end
                str = str .. tostring(v)
            end
            debug_output(str)  -- Эта функция будет зарегистрирована ниже
            original_print(...)  -- Сохраняем оригинальный вывод
        end
    )" );
	setCentralWidget( cntrl_wgt );
}


void
debug_console::_printToOutput( const QString& text )
{
	if ( _output )
		{
			_output->appendPlainText( text );
			_output->verticalScrollBar()->setValue(
				_output->verticalScrollBar()->maximum() );
		}
}

void
debug_console::execute_command()
{
	const QString command = _input->text().trimmed();
	_input->clear();

	if ( command.isEmpty() ) { return; }

	_printToOutput( "> " + command );

	try
		{
			// Пробуем выполнить как выражение (с return)
			sol::object result
				= ( *_ngn_ptr )->do_string( "return " + command.toStdString() );

			// Безопасное преобразование результата в строку
			sol::function tostring	 = ( *_ngn_ptr )->globals() [ "tostring" ];
			std::string	  result_str = tostring( result );
			_printToOutput( QString::fromStdString( result_str ) );
		}
	catch ( const sol::error& e )
		{
			try
				{
					( *_ngn_ptr )->do_string( command.toStdString() );
				}
			catch ( const sol::error& e )
				{
					_printToOutput( "Error: " + QString::fromStdString( e.what() ) );
				}
		}
	catch ( const std::exception& e )
		{
			_printToOutput( "System error: " + QString::fromStdString( e.what() ) );
		}
}
