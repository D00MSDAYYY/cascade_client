#pragma once

#include "actions_tree.hpp"
#include "script_engine.hpp"
#include "script_object.hpp"

#include <QGridLayout>
#include <QListWidget>
#include <QMainWindow>
#include <QScrollArea>
#include <QToolBar>

class alerts_page
	: public QMainWindow
	, public script::object
{
	Q_OBJECT

public:
	alerts_page( const std::string&	 name,
				 script::engine::ptr ngn_ptr,
				 QWidget*			 parent = nullptr );
	~alerts_page() { };

	const std::string
	class_name() const override
	{
		return "alerts_page";
	}

protected:
	virtual void
	self_register() override;

private:
	// QScrollArea* _scrl_area{new QScrollArea{this}};
	QToolBar*	 _tl_bar{};

	QListWidget* _lst_wgt{}; // TODO Mb change to QListView later

	std::map< std::string, sol::object >
		_tlbtns_lua_obj;	 //! TODO not only tlbtns, but all exposed objects

	struct _c_c_d_t
	{
		QAction*	_qaction{};
		std::string _script{};
	};

	using _nd_t = actions_tree::node< _c_c_d_t >;

	std::shared_ptr< _nd_t > _actions_tree_root{};
};
