#pragma once

#include "actions_tree.hpp"
#include "alert.hpp"
#include "page.hpp"

#include <QListWidget>
#include <QScrollArea>
#include <QToolBar>
#include <functional>
#include <unordered_map>

class alerts_page : public page
{
	Q_OBJECT

public:
	alerts_page( const std::string&			  name,
				 const scripting::engine::ptr ngn_ptr,
				 QWidget*					  parent = nullptr );
	~alerts_page() = default;

	CLASS_NAME_AS_STRING( alerts_page )
	MAKE_LUA_OBJECT_FROM_THIS()

	static void
	register_in_lua( const scripting::engine::ptr& ngn_ptr );


	std::multimap< std::string, sol::object >
	get_alerts();
	// TODO! mb add alert id as return to unique identifing (to store into alertist to
	// faster and convinient deletion)
	void
	add_alert( const alert& a ); 

	void
	remove_alert( const std::string& alert_name, const std::string& alertist_name );

	using comparator = std::function< bool( const alert& lhs, const alert& rhs ) >;
	void
	sort( comparator cmpr );	 // TODO! implement sorting (by name, tags, type, ... )

private:
	void
	_add_alert_to_list_widget( const std::shared_ptr< alert >& alert_ptr );

	struct _c_c_d_t
	{
		QAction*	_qaction{};
		std::string _script{};
	};

	using _nd_t = actions_tree::node< _c_c_d_t >;

	QToolBar*	 _tl_bar{};
	QListWidget* _lst_wgt{}; // TODO Mb change to QListView later

	std::multimap< std::string, std::shared_ptr< alert > > _alerts;
	std::shared_ptr< _nd_t >							   _actions_tree_root{};
};
