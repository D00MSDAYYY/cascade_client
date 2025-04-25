#pragma once

#include "page.hpp"
#include "scenario.hpp"

#include <QListWidget>
#include <functional>
#include <vector>

class scenarios_page : public page
{
	Q_OBJECT

public:
	scenarios_page( const std::string&	   name,
					scripting::engine::ptr ngn_ptr,
					QWidget*			   parent = nullptr );
	~scenarios_page();

	CLASS_NAME_AS_STRING( scenarios_page )
	MAKE_LUA_OBJECT_FROM_THIS()
	STATIC_REGISTER_IN_LUA()


	std::vector< sol::object >
	get_scenarios();
	// TODO! mb add alert id as return to unique identifing (to store into
	// alertist to faster and convinient deletion)

	void
	add_scenario( const scenario& a );

	void
	remove_scenario( const std::string& scenario_name );

	using comparator = std::function< bool( const scenario& lhs, const scenario& rhs ) >;
	void
	sort_scenarios( std::optional< comparator > cmpr_opt = std::nullopt );

private:
	void
											   _update_list_widget();

	QListWidget*							   _lst_wgt{};
	std::vector< std::shared_ptr< scenario > > _scenarios;
};
