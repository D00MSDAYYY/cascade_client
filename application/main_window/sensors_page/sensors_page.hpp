#pragma once

#include "page.hpp"
#include "sensor.hpp"

#include <QListWidget>

class sensors_page : public page
{
	Q_OBJECT

public:
	sensors_page( const std::string&		   name,
				  const scripting::engine::ptr ngn_ptr,
				  QWidget*					   parent = nullptr );
	~sensors_page();

	CLASS_NAME_AS_STRING( sensors_page )
	MAKE_LUA_OBJECT_FROM_THIS()
	STATIC_REGISTER_IN_LUA()


	std::vector< sol::object >
	get_sensors();

	void
	add_sensor( std::shared_ptr<sensor> sensor_ptr );

	void
	remove_sensor( const std::string& sensor_name );

	using comparator = std::function< bool( const sensor& lhs, const sensor& rhs ) >;
	void
	sort_sensors( std::optional< comparator > cmpr_opt = std::nullopt );

private:
	void
											 _update_list_widget();

	QListWidget*							 _lst_wgt{};
	std::vector< std::shared_ptr< sensor > > _sensors;
};
