
#include "alerts_page.hpp"

#include <QFrame>
#include <QInputDialog>
#include <QLabel>
#include <QListWidgetItem>
#include <QMenu>
#include <QMessageBox>
#include <QToolButton>
#include <QVBoxLayout>

alerts_page::alerts_page( const std::string&		   name,
						  const scripting::engine::ptr ngn_ptr,
						  QWidget*					   parent )
	: page{ name, ngn_ptr, parent }
{
	Q_INIT_RESOURCE( alerts_page );

	_tl_bar	 = new QToolBar{ "Tool bar", this };
	_lst_wgt = new QListWidget{ this };

	_tl_bar->setIconSize( { 32, 32 } );
	_tl_bar->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
	_tl_bar->setMovable( false );

	_actions_tree_root = std::make_shared< _nd_t >( _nd_t{
	  { .name		 = "_root_node",
		.description = "don't use this node ",
		.children	 = { _nd_t{ {
						   .name = "sort",
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
						  std::string{ ":alerts_page/icons/" + child._name + ".png" }
							  .c_str() }
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

	setCentralWidget( _lst_wgt );
	addToolBar( Qt::TopToolBarArea, _tl_bar );

	auto a{
		alert{ _ngn_ptr,
			   alert::TYPE::INFO,
			   "initial_alert", "0-0-0",
			   "some_text", "none" }
	};
	
	add_alert( a );

	self_register();
}

void
alerts_page::add_alert( alert& a )
{
	if ( auto [ range_start, range_end ]{ _alerts.equal_range( a.get_alertist_name() ) };
		 range_start == _alerts.end()
		 or not std::any_of( range_start, range_end, [ &a ]( const auto& pair ) {
				return pair.second->get_name() == a.get_name();
			} ) ) // check for uniqness of alert_name and alertist_name pair
		{
			auto alert_ptr = new alert( std::move( a ) );

			_alerts.insert(
				{ alert_ptr->get_name(), std::shared_ptr< alert >( alert_ptr ) } );

			auto item{ new QListWidgetItem() };
			auto frame{ new QFrame() };

			frame->setFrameShape( QFrame::StyledPanel );

			auto layout{ new QVBoxLayout( frame ) };

			auto nameLabel{ new QLabel(
				QString::fromStdString( alert_ptr->get_name() ) ) };
			auto textLabel{ new QLabel(
				QString::fromStdString( alert_ptr->get_text() ) ) };

			// switch ( type )
			// 	{
			// 		case alert::TYPE::ALARM :
			// 			frame->setStyleSheet(
			// 				"background: #e6f7ff; border: 1px solid #91d5ff;" );
			// 			break;
			// 		case alert::TYPE::WARNING :
			// 			frame->setStyleSheet(
			// 				"background: #fffbe6; border: 1px solid #ffe58f;" );
			// 			break;
			// 		case alert::TYPE::INFO :
			// 			frame->setStyleSheet(
			// 				"background: #fffbe6; border: 1px solid #ffe58f;" );
			// 			break;
			// 	}

			layout->addWidget( nameLabel );
			layout->addWidget( textLabel );

			item->setSizeHint( frame->sizeHint() );
			_lst_wgt->addItem( item );
			_lst_wgt->setItemWidget( item, frame );

			_lst_wgt->scrollToItem( item );
		}
	else { std::cout << "'aletist_name' and 'alert_name' is not a unique pair"; }
}

void
alerts_page::remove_alert( const std::string& alert_name,
						   const std::string& alertist_name )
{
	auto range{ _alerts.equal_range( alertist_name ) };

	for ( auto it{ range.first }; it != range.second; )
		{
			if ( it->second->get_name() == alert_name ) { it = _alerts.erase( it ); }
			else { ++it; }
		}
}

std::multimap< std::string, sol::object >
alerts_page::get_alerts()
{
	std::multimap< std::string, sol::object > tmp;
	for ( const auto& [ key, value ] : _alerts )
		{
			tmp.insert( { key, value->make_lua_object_from_this() } );
		}
	return tmp;
}

void
alerts_page::self_register()
{
	if ( can_self_register() )
		{
			auto type{ _ngn_ptr->new_usertype< alerts_page >( class_name(),
															  sol::base_classes,
															  sol::bases< page >() ) };
			type [ "get_alerts" ]	= &alerts_page::get_alerts;
			type [ "add_alert" ]	= &alerts_page::add_alert;
			type [ "remove_alert" ] = &alerts_page::remove_alert;
			type [ "sort" ]			= &alerts_page::sort;

			_ngn_ptr->new_enum< alert::TYPE >( "ALERT_TYPE",
											   {
												 { "ALARM",	alert::TYPE::ALARM   },
												 { "WARNING", alert::TYPE::WARNING },
												 { "INFO",	   alert::TYPE::INFO	 }
			   } );
		}
}
