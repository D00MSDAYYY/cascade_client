
#include "logbook_page.hpp"

#include <QInputDialog>
#include <QMessageBox>

logbook_page::logbook_page( const std::string&	name,
							script::engine::ptr ngn_ptr,
							QWidget*			parent )
	: page{name, ngn_ptr, parent}
{
	Q_INIT_RESOURCE( logbook_page );
	self_register();
}

logbook_page::~logbook_page() { Q_CLEANUP_RESOURCE( logbook_page ); }

sol::object
logbook_page::make_lua_object_from_this() const
{
	return sol::make_object( _ngn_ptr->lua_state(), this );
}

void
logbook_page::self_register()
{

		if ( can_self_register() )
			{
				auto type{ _ngn_ptr->new_usertype< logbook_page >(
					class_name(),
					sol::base_classes,
					sol::bases< page >() ) };
			}
	
}

