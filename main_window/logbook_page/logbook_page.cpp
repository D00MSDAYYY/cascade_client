
#include "logbook_page.hpp"

#include <QInputDialog>
#include <QMessageBox>

logbook_page::logbook_page( QWidget* parent )
	: QMainWindow{ parent }
{
	Q_INIT_RESOURCE( lp_icons );
}

