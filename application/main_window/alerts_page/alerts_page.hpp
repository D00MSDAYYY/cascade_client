#pragma once

#include "actions_tree.hpp"
#include "alert.hpp"
#include "page.hpp"

#include <QListWidget>
#include <QScrollArea>
#include <QToolBar>
#include <unordered_map>

class alerts_page : public page
{
	Q_OBJECT

public:
	alerts_page( const std::string&			  name,
				 const scripting::engine::ptr ngn_ptr,
				 QWidget*					  parent = nullptr );
	~alerts_page() = default;

	const std::string
	class_name() const override
	{
		return "alerts_page";
	}
// /////////////////////////////////////////////////////////////////
	// TODO! mb add alert id as return to unique identifing (to store into alertist to faster and convinient deletion)
	void
	add_alert( alert::TYPE								   type,
			   const std::string&						   alert_name,
			   const std::string&						   tp_str,
			   const std::string&						   text,
			   const std::string&						   alertist_name,
			   std::optional< std::vector< std::string > > tags = {} );

	void
	remove_alert( const std::string& alert_name, const std::string& alertist_name );

	std::multimap< std::string, sol::object >
	get_alerts();

	void
	sort() { }; // TODO! implement sorting (by name, tags, type, ... )

	// /////////////////////////////////////////////////////////////////

	virtual sol::object
	make_lua_object_from_this() const override
	{
		return sol::make_object( _ngn_ptr->lua_state(), this );
	};

protected:
	virtual void
	self_register() override;

private:
	QToolBar*	 _tl_bar{};
	QListWidget* _lst_wgt{}; // TODO Mb change to QListView later

	std::multimap< std::string, std::shared_ptr< alert > > _alerts;

	struct _c_c_d_t
	{
		QAction*	_qaction{};
		std::string _script{};
	};

	using _nd_t = actions_tree::node< _c_c_d_t >;

	std::shared_ptr< _nd_t > _actions_tree_root{};

	std::map< std::string, sol::object >
		_tlbtns_lua_obj; //! TODO not only tlbtns, but all exposed objects
};
