#pragma once

#include "scripting.hpp"

class chart : public scripting::object
{
public:
	chart( const std::string& name, const scripting::engine::ptr ngn_ptr )
		: scripting::object{ ngn_ptr } // to request for new points for plotting
		, _name{ name }
	{
	}

	~chart() = default;

	bool
	operator== ( const chart& c ) const
	{
		return _name == c._name; // TODO! mb change in the future
	}

private:
	const std::string _name{};
	// points???
};
