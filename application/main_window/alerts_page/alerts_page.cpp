
#include "alerts_page.hpp"

#include <QInputDialog>
#include <QMessageBox>

alerts_page::alerts_page( QWidget* parent )
	: QMainWindow{ parent }
{
	Q_INIT_RESOURCE( ap_icons );

	_tl_bar	 = new QToolBar{ "Tool bar", this };
	_lst_wgt = new QListWidget{ this };

	_tl_bar->setIconSize( { 32, 32 } );
	_tl_bar->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
	_tl_bar->setMovable( false );
	for ( const auto& [ str, func ] :
		  std::vector< std::pair< std::string, std::function< void() > > >{
			{ "filter",	[]() { return; } },
			{ "|",	   []() { return; } },
			{ "remove",	[]() { return; } },
			{ "|",	   []() { return; } },
			{ "history", []() { return; } }
	} )
		{
			if ( str == "|" ) { _tl_bar->addSeparator(); }
			else
				{
					auto path{ ":/ap_icons/" + str + ".png" };
					auto action{ _tl_bar->addAction(
						QIcon{ QPixmap{ path.c_str() }.scaled(
							_tl_bar->iconSize(),
							Qt::AspectRatioMode::KeepAspectRatio ) },
						str.c_str() ) };
					connect( action, &QAction::triggered, this, func );
				}
		}
	addToolBar( Qt::TopToolBarArea, _tl_bar );

	_lst_wgt->addItems( { { "Test1" }, { "Test2" } } );
	setCentralWidget( _lst_wgt );
}
