#pragma once

#include "actions_tree.hpp"
#include "alert.hpp"
#include "page.hpp"

#include <QListWidget>
#include <QScrollArea>
#include <QToolBar>

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

	void
	add_alert( alert::TYPE		  type,
			   const std::string& tp_str,
			   const std::string& text,
			   const std::string& alertist_name );
	void
	remove_alert( const std::string& alertist_name );

	void
	sort();

protected:
	virtual void
	self_register() override;

private:
	QToolBar*				   _tl_bar{};
	QListWidget*			   _lst_wgt{}; // TODO Mb change to QListView later

	std::vector< std::string > _alerts;
	std::vector< std::string > _warnings;

	std::map< std::string, sol::object >
		_tlbtns_lua_obj; //! TODO not only tlbtns, but all exposed objects

	struct _c_c_d_t
	{
		QAction*	_qaction{};
		std::string _script{};
	};

	using _nd_t = actions_tree::node< _c_c_d_t >;

	std::shared_ptr< _nd_t > _actions_tree_root{};
};
