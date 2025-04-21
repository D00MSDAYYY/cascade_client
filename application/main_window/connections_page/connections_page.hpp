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

	const std::string
	class_name() const override
	{
		return "connections_page";
	}

	void
	add_connection();
	void
	remove_connection();

	void //?
	get_connections_creator();

	virtual sol::object
	make_lua_object_from_this() const override
	{
		return sol::make_object( _ngn_ptr->lua_state(), this );
	};

protected:
	virtual void
	self_register() override;

private:
	void
				 _redistributeWidgets();
	QGridLayout* _snsrs_grd{};
	QWidget*	 _snsrs_pln{};

	QScrollArea* _scrl_area{};

	QToolBar*	 _tl_bar{};
};
