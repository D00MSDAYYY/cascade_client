#pragma once

#include "script_engine.hpp"
#include "script_object.hpp"

#include <QGridLayout>
#include <QMainWindow>
#include <QScrollArea>
#include <QToolBar>

class scenarios_page
	: public QMainWindow
	, public script::object
{
	Q_OBJECT

public:
	scenarios_page( const std::string&	name,
					script::engine::ptr ngn_ptr,
					QWidget*			parent = nullptr );
	~scenarios_page() ;

	const std::string
	class_name() const override
	{
		return "scenarios_page";
	}

protected:
	virtual void
	self_register() override{};

private:
	QToolBar* _tl_bar{};
};
