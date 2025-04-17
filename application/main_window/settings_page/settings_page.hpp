#pragma once

#include "page.hpp"

class settings_page : public page
{
	Q_OBJECT

public:
	settings_page( const std::string&			name,
				   const scripting::engine::ptr ngn_ptr,
				   QWidget*						parent = nullptr );
	~settings_page() = default;

	const std::string
	class_name() const override
	{
		return "settings_page";
	}

protected:
	virtual void
	self_register() override;

private:
};
