#include "sensor.hpp"

sensor::sensor( const std::string& name, scripting::engine::ptr ngn_ptr, QWidget* parent )
	: _name{ name }
	, scripting::object{ ngn_ptr }
	, QWidget{ parent }
{
}

void
sensor::on()
{
	if ( _wrkng_state != WORKING_STATE::OFF )
		{
			std::cout << "sensor is already turned on or suspended" << std::endl;
			return;
		}
	_wrkng_state = WORKING_STATE::ON;
}

void
sensor::off()
{
	if ( _wrkng_state == WORKING_STATE::OFF )
		{
			std::cout << "sensor is already turned off" << std::endl;
			return;
		}
	_wrkng_state = WORKING_STATE::OFF;
}

void
sensor::suspend()
{
	if ( _wrkng_state != WORKING_STATE::ON )
		{
			std::cout << "can't suspend, page is off" << std::endl;
			return;
		}
	_wrkng_state = WORKING_STATE::SUSPENDED;
}

void
sensor::resume()
{
	if ( _wrkng_state != WORKING_STATE::SUSPENDED )
		{
			std::cout << "can't resume, page is not suspended";
			return;
		}
	_wrkng_state = WORKING_STATE::SUSPENDED;
};

void
sensor::register_in_lua( const scripting::engine::ptr& ngn_ptr )
{
	if ( can_register_in_lua< sensor >( ngn_ptr ) )
		{
			auto type{ ngn_ptr->new_usertype< sensor >( _class_name ) };

			type [ "on" ]	   = []() { };
			type [ "off" ]	   = []() { };
			type [ "suspend" ] = []() { };
			type [ "resume" ]  = []() { };
		}
	std::cout << _class_name << "\t is registered" << std::endl;
}

void
sensor::update()
{
	if ( _wrkng_state != sensor::WORKING_STATE::ON ) { return; }
}

