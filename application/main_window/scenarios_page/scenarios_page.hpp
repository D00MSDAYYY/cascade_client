#pragma once

#include "page.hpp"

#include <QToolBar>

class scenarios_page
	: public page
{
	Q_OBJECT

public:
	scenarios_page( const std::string&	name,
					scripting::engine::ptr ngn_ptr,
					QWidget*			parent = nullptr );
	~scenarios_page() ;

	const std::string
	class_name() const override
	{
		return "scenarios_page";
	}

	void add_scenario();
	void remove_scenario();

protected:
	virtual void
	self_register() override;

private:
	QToolBar* _tl_bar{};
};
