#pragma once

#include "scripting.hpp"

#include <QHBoxLayout>
#include <QWidget>

class sensor
	: public QWidget
	, public scripting::object
{
	Q_OBJECT

public:
	sensor( const std::string&	   name,
			scripting::engine::ptr ngn_ptr,
			QWidget*			   parent = nullptr );
	~sensor() = default;

	CLASS_NAME_AS_STRING( sensor )
	MAKE_LUA_OBJECT_FROM_THIS()
	STATIC_REGISTER_IN_LUA()

	void
	on();	 // TODO! i deleted on_... func mb it is a mistake? 	 

	void
	off();

	void
	suspend();

	void
	resume();

	void
	update();

	void
	subscribe_to( sol::object obj );
	void
	unsubscribe_from( sol::object obj );

	void
	add_subscriber( const std::string& name, sol::object obj );
	void
	remove_subscriber( sol::object obj );


	std::map< std::string, sol::object >
	get_subscribers();
	std::map< std::string, sol::object >
	get_subscriptions();

	auto
	get_name() const
	{
		return _name;
	}

	enum class WORKING_STATE
	{
		ON,
		OFF,
		SUSPENDED
	};

	WORKING_STATE
	get_state() const { return _wrkng_state; };

	std::string
	get_report() const
	{
		return "default empty report";
	}

	bool
	operator== ( const sensor& s ) const
	{
		return _name == s._name; // TODO! mb change in the future
	}

private:
	QHBoxLayout*						 _layout;
	std::map< std::string, sol::object > _widgets;

	std::vector< sol::object >			 _subscribers;
	std::map< std::string, sol::object > _subscriptions;


	WORKING_STATE						 _wrkng_state{ WORKING_STATE::OFF };
	const std::string					 _name;
};
