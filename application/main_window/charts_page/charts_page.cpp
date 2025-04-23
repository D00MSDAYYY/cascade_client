#include "charts_page.hpp"

charts_page::charts_page( const std::string&  name,
						  const scripting::engine::ptr ngn_ptr,
						  QWidget*			  parent )
	: page{name, ngn_ptr, parent}
{
	Q_INIT_RESOURCE( charts_page );

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
					auto path{ ":/charts_page/icons/" + str + ".png" };
					auto action{ _tl_bar->addAction(
						QIcon{ QPixmap{ path.c_str() }.scaled(
							_tl_bar->iconSize(),
							Qt::AspectRatioMode::KeepAspectRatio ) },
						str.c_str() ) };
					connect( action, &QAction::triggered, this, func );
				}
		}

	addToolBar( Qt::TopToolBarArea, _tl_bar );
	register_in_lua(*_ngn_ptr);
}

charts_page::~charts_page() { Q_CLEANUP_RESOURCE( charts_page ); }

void
charts_page::register_in_lua(const scripting::engine::ptr& ngn_ptr)
{
	if ( can_register_in_lua<charts_page>(ngn_ptr) )
		{
			auto type{ ngn_ptr->new_usertype< charts_page >( _class_name,
															  sol::base_classes,
															  sol::bases< page >() ) };
		}
}

