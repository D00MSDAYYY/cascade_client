#pragma once

#include "page.hpp"


#include <QGridLayout>
#include <QScrollArea>
#include <QToolBar>

class connections_page
	: public page
{
	Q_OBJECT

public:
	connections_page( const std::string&  name,
					  script::engine::ptr ngn_ptr,
					  QWidget*			  parent = nullptr );
	~connections_page() { };

	void
	addConnection();
	void
	removeConnection();

	const std::string
	class_name()const  override
	{
		return "connections_page";
	}

	sol::object
	create_lua_object_from_this() const override;

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
