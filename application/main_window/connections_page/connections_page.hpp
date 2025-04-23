#pragma once

#include "page.hpp"

#include <QGridLayout>
#include <QScrollArea>
#include <QToolBar>

class connections_page : public page
{
	Q_OBJECT

public:
	connections_page( const std::string&  name,
					  const scripting::engine::ptr ngn_ptr,
					  QWidget*			  parent = nullptr );
	~connections_page() = default;

	void
	addConnection();
	void
	removeConnection();

	CLASS_NAME_AS_STRING(connections_page)

	void
	add_connection();
	void
	remove_connection();

	void //?
	get_connections_creator();

	static void
	register_in_lua( const scripting::engine::ptr& ngn_ptr );

private:
	void
				 _redistributeWidgets();
	QGridLayout* _snsrs_grd{};
	QWidget*	 _snsrs_pln{};

	QScrollArea* _scrl_area{};

	QToolBar*	 _tl_bar{};
};
