#pragma once

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
	class_name() override
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
};
