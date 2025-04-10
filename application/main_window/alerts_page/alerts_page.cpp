
#include "alerts_page.hpp"

#include <QInputDialog>
#include <QMenu>
#include <QMessageBox>
#include <QToolButton>

alerts_page::alerts_page( const std::string&  name,
						  script::engine::ptr ngn_ptr,
						  QWidget*			  parent )
	: page{name, ngn_ptr, parent}
{
	Q_INIT_RESOURCE( alerts_page );

	_tl_bar = new QToolBar{ "Tool bar", this };

	_tl_bar->setIconSize( { 32, 32 } );
	_tl_bar->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
	_tl_bar->setMovable( false );

	_actions_tree_root = std::make_shared< _nd_t >( _nd_t{
	  { .name		 = "_root_node",
		.description = "don't use this node ",
		.children	 = { _nd_t{ {
						   .name = "filter",
						 } },
						 _nd_t{ {
						   .name = "|",
						 } },
						 _nd_t{ {
						   .name = "remove",
						 } },
						 _nd_t{ { .name = "|" } },
						 _nd_t{ {
						   .name = "history",
						 } } } }
	  } );
	std::function< void( _nd_t& ) > fill_empty_node_fields{};
	fill_empty_node_fields = [ this, &fill_empty_node_fields ]( _nd_t& node ) -> void {
		for ( auto& child : node._children )
			{
				fill_empty_node_fields( child );
				child._data._qaction = new QAction{
					QIcon(
						QPixmap{
						  std::string{ ":alerts_page/icons/" + child._name + ".png" }.c_str() }
							.scaled( iconSize(), Qt::AspectRatioMode::KeepAspectRatio ) ),
					child._name.c_str(),
					this
				};
				QObject::connect(
					child._data._qaction,
					&QAction::triggered,
					[ this, child ]() { _ngn_ptr->script( child._data._script ); } );
				////////////////////////////////////////////////
				// //
				// add filling the scripts here as well    //
				// //
				////////////////////////////////////////////////
			}
	};
	fill_empty_node_fields( *_actions_tree_root );


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
	for ( auto& group : _actions_tree_root->_children )
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


	addToolBar( Qt::TopToolBarArea, _tl_bar );

	_lst_wgt = new QListWidget{ this };
	_lst_wgt->addItems( { { "Test1" }, { "Test2" }, { "Test3" }, { "Test4" } } );
	setCentralWidget( _lst_wgt );

	self_register();
}

sol::object
alerts_page::create_lua_object_from_this() const
{
	return sol::make_object(_ngn_ptr->lua_state(), this);
}

void
alerts_page::self_register()
{
	if ( can_self_register() )
		{
			auto type{ _ngn_ptr->new_usertype< alerts_page >( class_name(),
															  sol::base_classes,
															  sol::bases< page >() ) };
			type [ "special_func_ap" ] = []() { return "hello from spec func for ap"; };
		}
}
