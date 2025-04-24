
#include "alerts_page.hpp"

#include <QFrame>
#include <QInputDialog>
#include <QLabel>
#include <QListWidgetItem>
#include <QMenu>
#include <QMessageBox>
#include <QToolButton>
#include <QVBoxLayout>


static alerts_page::comparator compare_by_name{ []( const alert& lhs,
													const alert& rhs ) -> bool {
	std::cout << "compare_by_name triggered" << std::endl;
	return lhs.get_name() < rhs.get_name();
} };

static alerts_page::comparator compare_by_date{ []( const alert& lhs,
													const alert& rhs ) -> bool {
	std::cout << "compare_by_date triggered" << std::endl;
	return lhs.get_timepoint() < rhs.get_timepoint();
} };

static alerts_page::comparator compare_by_type{ []( const alert& lhs,
													const alert& rhs ) -> bool {
	std::cout << "compare_by_type triggered" << std::endl;
	return static_cast< int >( lhs.get_type() ) < static_cast< int >( rhs.get_type() );
} };

alerts_page::alerts_page( const std::string&		   name,
						  const scripting::engine::ptr ngn_ptr,
						  QWidget*					   parent )
	: page{ name, ngn_ptr, parent }
{
	Q_INIT_RESOURCE( alerts_page );
	register_in_lua( *_ngn_ptr );

	_tl_bar	 = new QToolBar{ "Tool bar", this };
	_lst_wgt = new QListWidget{ this };

	_tl_bar->setIconSize( { 32, 32 } );
	_tl_bar->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
	_tl_bar->setMovable( false );


	auto bind_action_comparator
		= [ this ]( QAction* action, auto comparator ) -> QAction* {
		connect( action, &QAction::triggered, [ this, comparator ]() {
			this->sort( comparator );
		} );
		return action;
	};

	_actions_tree_root = std::make_shared< _nd_t >( _nd_t{
	  { .name		 = "_root_node",
		.description = "don't use this node ",
		.children
		= { _nd_t{ { .name	   = "sort",
					 .children = { _nd_t{ { .name = "by name",
											.data = { ._qaction = bind_action_comparator(
														  new QAction{ this },
														  compare_by_name ) } } },
								   _nd_t{ { .name = "by date",
											.data = { ._qaction = bind_action_comparator(
														  new QAction{ this },
														  compare_by_date ) } } },
								   _nd_t{ { .name = "by type",
											.data = { ._qaction = bind_action_comparator(
														  new QAction{ this },
														  compare_by_type ) } } } } } },
			_nd_t{ {
			  .name = "|",
			} },
			_nd_t{ {
			  .name = "remove",
			} },
			_nd_t{ {
			  .name = "select",
			} } } }
	} );
	std::function< void( _nd_t& ) > fill_empty_node_fields{};
	fill_empty_node_fields = [ this, &fill_empty_node_fields ]( _nd_t& node ) -> void {
		for ( auto& child : node._children )
			{
				fill_empty_node_fields( child );

				auto old_action{ child._data._qaction };

				child._data._qaction = new QAction{
					QIcon(
						QPixmap{
						  std::string{ ":alerts_page/icons/" + child._name + ".png" }
							  .c_str() }
							.scaled( iconSize(), Qt::AspectRatioMode::KeepAspectRatio ) ),
					child._name.c_str(),
					this
				};

				QObject::connect( child._data._qaction,
								  &QAction::triggered,
								  [ this, child, old_action ]() {
									  if ( old_action ) { old_action->trigger(); }
									  ( *_ngn_ptr )->script( child._data._script );
								  } );
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


	add_alert( alert{ alert::TYPE::INFO,
					  "a_alert",
					  "00-00-01",
					  "some_text",
					  "temperature sensor" } );
	add_alert( alert{ alert::TYPE::WARNING,
					  "c_alert",
					  "00-00-02",
					  "some_some_text",
					  "CO2 sensor" } );
	add_alert( alert{ alert::TYPE::ALARM,
					  "b_alert",
					  "00-00-03",
					  "some_some_some_text",
					  "light sensor" } );

	// auto a = ( *_ngn_ptr )
	// 			 ->script( "return alert.new(alert.TYPE.INFO, 'hell', "
	// 					   "tostring(cascade_client.clock:now()), 'test "
	// 					   "text str ',' wowo ')" );

	// auto	   obj	 = make_lua_object_from_this();
	// sol::table table = obj.as< sol::table >();
	// table [ "add_alert" ]( this, a.get< alert >() );
}

void
alerts_page::add_alert( const alert& a )
{
	if ( auto [ range_start, range_end ]{ _alerts.equal_range( a.get_alertist_name() ) };
		 range_start == _alerts.end()
		 or not std::any_of( range_start, range_end, [ &a ]( const auto& pair ) {
				return pair.second->get_name() == a.get_name();
			} ) ) // check for uniqness of alert_name and alertist_name pair
		{
			auto alert_ptr{ std::shared_ptr< alert >( new alert( std::move( a ) ) ) };

			_alerts.insert( { alert_ptr->get_name(), alert_ptr } );

			_add_alert_to_list_widget( alert_ptr );
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

void
alerts_page::sort( comparator cmpr )
{
	std::vector< std::pair< std::string, std::shared_ptr< alert > > > tmp{
		_alerts.begin(),
		_alerts.end()
	};
	std::sort( tmp.begin(), tmp.end(), [ cmpr ]( const auto& lhs, const auto& rhs ) {
		const auto& lhs_alert{ lhs.second };
		const auto& rhs_alert{ rhs.second };

		return cmpr( *lhs_alert, *rhs_alert );
	} );
	_lst_wgt->clear();
	for ( const auto& [ name, ptr ] : tmp ) { _add_alert_to_list_widget( ptr ); }
}

void
alerts_page::_add_alert_to_list_widget( const std::shared_ptr< alert >& alert_ptr )
{
	// Создаем основной фрейм
	auto frame = new QFrame();
	frame->setFrameShape( QFrame::StyledPanel );
	frame->setMinimumHeight( 80 ); // Фиксированная высота для красоты

	// Устанавливаем стиль в зависимости от типа alert
	QString styleSheet;
	switch ( alert_ptr->get_type() )
		{
			case alert::TYPE::INFO : styleSheet = "background:rgb(0, 29, 97);"; break;
			case alert::TYPE::WARNING :
				styleSheet = "background:rgb(121, 117, 0); ";
				break;
			case alert::TYPE::ALARM : styleSheet = "background:rgb(102, 14, 0); "; break;
		}
	frame->setStyleSheet( styleSheet );

	// Главный layout
	auto mainLayout = new QVBoxLayout( frame );
	mainLayout->setContentsMargins( 10, 10, 10, 10 );
	mainLayout->setSpacing( 5 );

	// Первая строка - заголовок (имя и тип)
	auto	headerLayout = new QHBoxLayout();

	// Иконка типа
	QLabel* typeIcon	 = new QLabel();
	QString iconPath;
	switch ( alert_ptr->get_type() )
		{
			case alert::TYPE::INFO : iconPath = ":alerts_page/icons/info.png"; break;
			case alert::TYPE::WARNING :
				iconPath = ":alerts_page/icons/warning.png";
				break;
			case alert::TYPE::ALARM : iconPath = ":alerts_page/icons/alarm.png"; break;
		}
	typeIcon->setPixmap( QPixmap( iconPath ).scaled( 20, 20 ) );
	headerLayout->addWidget( typeIcon );

	// Название alert (жирным)
	auto nameLabel = new QLabel(
		QString( "<b>%1</b>" ).arg( QString::fromStdString( alert_ptr->get_name() ) ) );
	nameLabel->setStyleSheet( "font-size: 12pt;" );
	headerLayout->addWidget( nameLabel );
	headerLayout->addStretch();

	// Время (серым цветом)
	auto timeLabel = new QLabel( QString::fromStdString( alert_ptr->get_timepoint() ) );
	timeLabel->setStyleSheet( "color: #666666; font-size: 10pt;" );
	headerLayout->addWidget( timeLabel );

	mainLayout->addLayout( headerLayout );

	// Текст alert
	auto textLabel = new QLabel( QString::fromStdString( alert_ptr->get_text() ) );
	textLabel->setWordWrap( true );
	textLabel->setStyleSheet( "font-size: 11pt; margin-top: 5px;" );
	mainLayout->addWidget( textLabel );

	// Третья строка - теги (если есть)
	if ( !alert_ptr->get_tags().empty() )
		{
			auto tagsLayout = new QHBoxLayout();
			tagsLayout->addWidget( new QLabel( "Tags:" ) );

			for ( const auto& tag : alert_ptr->get_tags() )
				{
					auto tagLabel = new QLabel( QString::fromStdString( tag ) );
					tagLabel->setStyleSheet( "background: #f0f0f0;"
											 "border-radius: 3px;"
											 "padding: 2px 5px;"
											 "margin-right: 5px;" );
					tagsLayout->addWidget( tagLabel );
				}

			tagsLayout->addStretch();
			mainLayout->addLayout( tagsLayout );
		}

	// Создаем элемент списка
	auto item = new QListWidgetItem();
	item->setSizeHint( frame->sizeHint() );
	item->setData(
		Qt::UserRole,
		QString::fromStdString( alert_ptr->get_name() ) ); // Сохраняем имя для поиска

	_lst_wgt->addItem( item );
	_lst_wgt->setItemWidget( item, frame );
	_lst_wgt->scrollToItem( item );
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
alerts_page::register_in_lua( const scripting::engine::ptr& ngn_ptr )
{
	if ( can_register_in_lua< alerts_page >( ngn_ptr ) )
		{
			alert::register_in_lua( ngn_ptr );

			auto type{ ngn_ptr->new_usertype< alerts_page >( _class_name,
															 sol::base_classes,
															 sol::bases< page >() ) };
			type [ "get_alerts" ]	= &alerts_page::get_alerts;
			type [ "add_alert" ]	= &alerts_page::add_alert;
			type [ "remove_alert" ] = &alerts_page::remove_alert;
			type [ "sort" ]			= &alerts_page::sort;
		}
	std::cout << _class_name << "\t is registered" << std::endl;
}
