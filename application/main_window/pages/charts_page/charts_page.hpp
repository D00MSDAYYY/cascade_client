#pragma once

#include "chart.hpp"
#include "page.hpp"

#include <QListWidget>

class charts_page : public page
{
	Q_OBJECT

public:
	charts_page( const std::string&			  name,
				 const scripting::engine::ptr ngn_ptr,
				 QWidget*					  parent = nullptr );
	~charts_page();

	CLASS_NAME_AS_STRING( charts_page )
	MAKE_LUA_OBJECT_FROM_THIS()
	STATIC_REGISTER_IN_LUA()

	std::vector< sol::object >
	get_charts();
	// TODO! mb add chart id as return to unique identifing (to store into alertist to
	// faster and convinient deletion)
	void
	add_chart( const chart& a );

	void
	remove_chart( const std::string& chart_name );

	using comparator = std::function< bool( const chart& lhs, const chart& rhs ) >;
	void
	sort_charts( std::optional< comparator > cmpr_opt = std::nullopt );

private:
	void
	_update_list_widget();

	struct _c_c_d_t
	{
		QAction*	_qaction{};
		std::string _script{};
	};

	using _nd_t = actions_tree::node< _c_c_d_t >; // TODO! in future remove duplication of
												  // this struct in classes and locate in
												  // one place if possible

	QListWidget*							_lst_wgt{};

	std::vector< std::shared_ptr< chart > > _charts;
};
