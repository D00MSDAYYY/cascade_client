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

	auto
	get_name() const
	{
		auto		obj{ make_lua_object_from_this() };
		auto		obj_tbl{ obj.as< sol::table >() };
		std::string self_name{ obj_tbl [ "name" ] };
		return self_name;
	}

	bool
	operator== ( const sensor& s ) const
	{
		return get_name() == s.get_name(); // TODO! mb change in the future
	}


private:
	QHBoxLayout* _layout; //! decide to move main logic in lua code in self_register func
	std::map< std::string, QWidget > _widgets;
};
