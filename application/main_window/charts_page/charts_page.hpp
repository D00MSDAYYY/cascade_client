#pragma once

#include "script_engine.hpp"
#include "script_object.hpp"

#include <QGridLayout>
#include <QMainWindow>
#include <QScrollArea>
#include <QToolBar>

class charts_page
	: public QMainWindow
	, script::object
{
	Q_OBJECT

public:
	charts_page( const std::string&	 name,
				 script::engine::ptr ngn_ptr,
				 QWidget*			 parent = nullptr );
	~charts_page() { };

	void
	addConnection();
	void
	removeConnection();

	const std::string
	class_name() const override
	{
		return "charts_page";
	}

protected:
	virtual void
	self_register() override{};

private:
	void
				 _redistributeWidgets();

	QGridLayout* _snsrs_grd{};
	QWidget*	 _snsrs_pln{};
	QScrollArea* _scrl_area{};
	QToolBar*	 _tl_bar{};
};
