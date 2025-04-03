
#include "scenarios_page.hpp"

#include <QInputDialog>
#include <QMessageBox>

scenarios_page::scenarios_page( const std::string&	name,
								script::engine::ptr ngn_ptr,
								QWidget*			parent )
	: QMainWindow{ parent }
	, script::object{ name, ngn_ptr }
{
	Q_INIT_RESOURCE( scn_icons );
	_tl_bar = new QToolBar{ "Tool bar", this };

	_tl_bar->setIconSize( { 32, 32 } );
	_tl_bar->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
	_tl_bar->setMovable( false );
	for ( const auto& [ str, func ] :
		  std::vector< std::pair< std::string, std::function< void() > > >{
			{ "filter",	[]() { return; } },
			{ "|",	   []() { return; } },
			{ "add",	 []() { return; } },
			{ "remove",	[]() { return; } },
			{ "select",	[]() { return; } },
			{ "|",	   []() { return; } },
			{ "resume",	[]() { return; } },
			{ "suspend", []() { return; } }
	} )
		{
			if ( str == "|" ) { _tl_bar->addSeparator(); }
			else
				{
					auto path{ ":/scn_icons/" + str + ".png" };
					auto action{ _tl_bar->addAction(
						QIcon{ QPixmap{ path.c_str() }.scaled(
							_tl_bar->iconSize(),
							Qt::AspectRatioMode::KeepAspectRatio ) },
						str.c_str() ) };
					connect( action, &QAction::triggered, this, func );
				}
		}
	addToolBar( Qt::TopToolBarArea, _tl_bar );
}
