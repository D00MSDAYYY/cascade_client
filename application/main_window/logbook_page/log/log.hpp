#pragma once

#include "page.hpp"

class logbook_page : public page
{
	Q_OBJECT

public:
	logbook_page( const std::string&  name,
				  const scripting::engine::ptr ngn_ptr,
				  QWidget*			  parent = nullptr );
	~logbook_page();

	const std::string
	class_name() const override
	{
		return "logbook_page";
	}

	void
	set_timestamp();
	void		//! what timestamp?
	get_timestamp();

	void
	set_text( const std::string& content_str );
	std::string //! json str?
	get_text();

	void		// !
	set_reporter();
	void		// !
	get_reporter();

protected:
	virtual void
	self_register() override;

private:
};
