
#include "logbook_page.hpp"

#include <QInputDialog>
#include <QMessageBox>

logbook_page::logbook_page( const std::string&	name,
							script::engine::ptr ngn_ptr,
							QWidget*			parent )
	: QMainWindow{ parent }
	, script::object{ name, ngn_ptr }
{
	Q_INIT_RESOURCE( logbook_page );
}

logbook_page::~logbook_page() { Q_CLEANUP_RESOURCE( logbook_page ); }

