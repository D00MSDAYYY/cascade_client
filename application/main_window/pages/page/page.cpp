#include "page.hpp"

page::page( const std::string&			 name,
			const scripting::engine::ptr ngn_ptr,
			QWidget*					 parent )
	: QMainWindow( parent )
	, scripting::object{ ngn_ptr }
	, _name{ name }
{
	_tl_bar = new QToolBar( "Toolbar" );
	addToolBar( Qt::TopToolBarArea, _tl_bar );
	_tl_bar->setIconSize( { 32, 32 } );
	_tl_bar->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
	_tl_bar->setMovable( false );
};

void
page::_init_toolbar( _nd_t& actions_tree_root)
{
	std::function< void( _nd_t& ) >
		fill_empty_node_fields{}; // TODO! move this aux function in page.hpp to common
								  // use
	fill_empty_node_fields = [ this, &fill_empty_node_fields ]( _nd_t& node ) -> void {
		for ( auto& child : node._children )
			{
				fill_empty_node_fields( child );

				auto old_action{ child._data._qaction };

				auto path_str{ QString{ ":" } + _name.c_str() + "_page/icons/"
							   + child._name.c_str() + ".png" };

				child._data._qaction = new QAction{
					QIcon( QPixmap{path_str }
							   .scaled( iconSize(),
										Qt::AspectRatioMode::KeepAspectRatio ) ),
					child._name.c_str(),
					this
				};

				QObject::connect( child._data._qaction,
								  &QAction::triggered,
								  [ this, child, old_action ]() {
									  if ( old_action ) { old_action->trigger(); }
									  _ngn_ptr.value()->script( child._data._script );
								  } );
				////////////////////////////////////////////////
				// //
				// add filling the scripts here as well    //
				// //
				////////////////////////////////////////////////
			}
	};
	fill_empty_node_fields( actions_tree_root );

	std::function< QMenu*( const std::vector< _nd_t >& ) > create_button_menu{};
	create_button_menu
		= [ this, &create_button_menu ]( const std::vector< _nd_t >& nodes ) -> QMenu* {
		auto menu{ new QMenu( this ) };

		for ( const auto& node : nodes )
			{
				if ( node._children.empty() ) { menu->addAction( node._data._qaction ); }
				else
					{
						auto sub_menu{ create_button_menu( node._children ) };
						sub_menu->setTitle( node._name.c_str() );
						sub_menu->setIcon( node._data._qaction->icon() );
						menu->addMenu( sub_menu );
					}
			}
		return menu;
	};

	for ( auto& group : actions_tree_root._children )
		{
			if ( group._name == "|" ) { _tl_bar->addSeparator(); }
			else
				{
					auto btn{ new QToolButton{
					  _tl_bar } }; // !TODO switch to tool_button implementation from MOTH
					btn->setDefaultAction( group._data._qaction );
					btn->setSizePolicy( QSizePolicy::Preferred, QSizePolicy::Preferred );
					btn->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );

					if ( !group._children.empty() )
						{
							btn->setMenu( create_button_menu( group._children ) );
							btn->setPopupMode( QToolButton::InstantPopup );
						}
					_tl_bar->addWidget( btn );
				}
		}
}
