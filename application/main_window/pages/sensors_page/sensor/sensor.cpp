#include "sensor.hpp"

#include "ui_toolkit.hpp"

#include <QFile>

sensor::sensor( const std::string& name, scripting::engine::ptr ngn_ptr, QWidget* parent )
	: scripting::object{ ngn_ptr }
	, QWidget{ parent }
{
}

void
sensor::register_in_lua( const scripting::engine::ptr& ngn_ptr )
{
	if ( can_register_in_lua< sensor >( ngn_ptr ) )
		{
			Q_INIT_RESOURCE( sensor );

			ui_toolkit::register_in_lua( ngn_ptr );

			if ( QFile file( ":sensor/scripts/sensor.lua" );
				 file.open( QIODevice::ReadOnly | QIODevice::Text ) )
				{
					QTextStream in{ &file };
					auto		str{ in.readAll().toStdString() };
					file.close();
					ngn_ptr->script( str );
					std::cout << _class_name << "\t is registered" << std::endl;
				}
			else { std::cout << "can't open file sensor.lua" << std::endl; }
			

			Q_CLEANUP_RESOURCE( sensor );
		}
}
