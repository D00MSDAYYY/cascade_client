
#include "logbook_page.hpp"

#include <QInputDialog>
#include <QMessageBox>

logbook_page::logbook_page( const std::string&	   name,
							scripting::engine::ptr ngn_ptr,
							QWidget*			   parent )
	: page{ name, ngn_ptr, parent }
{
	Q_INIT_RESOURCE( logbook_page );
	register_in_lua(*_ngn_ptr);
}

logbook_page::~logbook_page() { Q_CLEANUP_RESOURCE( logbook_page ); }

void
logbook_page::register_in_lua(const scripting::engine::ptr& ngn_ptr)
{
	if ( can_register_in_lua<logbook_page>(ngn_ptr) )
		{
			auto type{ ngn_ptr->new_usertype< logbook_page >( _class_name,
															   sol::base_classes,
															   sol::bases< page >() ) };
		}
}

