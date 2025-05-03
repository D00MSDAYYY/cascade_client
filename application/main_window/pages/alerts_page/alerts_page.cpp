
#include "alerts_page.hpp"

#include <QFrame>
#include <QLabel>
#include <QListWidgetItem>
#include <QMenu>
#include <QToolButton>
#include <QVBoxLayout>

static alerts_page::comparator compare_by_name{ []( const alert& lhs,
													const alert& rhs ) -> bool {
	return lhs.get_name() < rhs.get_name();
} };

static alerts_page::comparator compare_by_date{ []( const alert& lhs,
													const alert& rhs ) -> bool {
	return lhs.get_timepoint() < rhs.get_timepoint();
} };

static alerts_page::comparator compare_by_type{ []( const alert& lhs,
													const alert& rhs ) -> bool {
	return static_cast< int >( lhs.get_type() ) < static_cast< int >( rhs.get_type() );
} };

alerts_page::alerts_page( const std::string&		   name,
						  const scripting::engine::ptr ngn_ptr,
						  QWidget*					   parent )
	: page{ name, ngn_ptr, parent }
{
	Q_INIT_RESOURCE( alerts_page );
	register_in_lua( *_ngn_ptr );

	_lst_wgt		   = new QListWidget{ this };

	_nd_t _actions_tree_root = _nd_t{ _nd_t{
	  { .name		 = "_root_node",
		.description = "don't use this node ",
		.children
		= { _nd_t{ { .name = "sort",
					 .children
					 = { _nd_t{ { .name = "by name",
								  .data = { ._qaction = _bind_qaction_with_func( new QAction{ this },
																				 [ this ]( auto _ ) {
																					 sort_alerts(
																						 compare_by_name );
																				 } ) } } },
						 _nd_t{ { .name = "by date",
								  .data = { ._qaction = _bind_qaction_with_func( new QAction{ this },
																				 [ this ]( auto _ ) {
																					 sort_alerts(
																						 compare_by_date );
																				 } ) } } },
						 _nd_t{ { .name = "by type",
								  .data = { ._qaction = _bind_qaction_with_func( new QAction{ this },
																				 [ this ]( auto _ ) {
																					 sort_alerts(
																						 compare_by_type );
																				 } ) } } } } } },
			_nd_t{ {
			  .name = "|",
			} },
			_nd_t{
			  { .name = "remove",
				.data
				= { ._qaction
					= _bind_qaction_with_func( new QAction{ this }, [ this ]( auto remove_action ) {
						  auto con{ connect(
							  _lst_wgt,
							  &QListWidget::itemClicked,
							  [ this ]( QListWidgetItem* item ) {
								  if ( auto frame_ptr{ qobject_cast< QFrame* >(
										   _lst_wgt->itemWidget( item ) ) } )
									  {
										  auto alert_ptr{
											  frame_ptr->property( "alert_ptr" )
												  .value< std::shared_ptr< alert > >()
										  };
										  remove_alert( alert_ptr->get_name(),
														alert_ptr->get_alertist_name() );
										  sort_alerts();
									  }
							  } ) };

						  QList< QAction* > saved_actions{};
						  for ( const auto& action_ptr : _tl_bar->actions() )
							  {
								  saved_actions.append( action_ptr );
							  }

						  auto exit_action{
							  new QAction{
		QIcon( QPixmap{
								  std::string{ ":alerts_page/icons/exit.png" }.c_str() }
										   .scaled(
											   iconSize(),
	   Qt::AspectRatioMode::KeepAspectRatio ) ),
		"exit", this }
						  };
						  connect( exit_action,
								   &QAction::triggered,
								   [ this, saved_actions, con ]() {
									   _tl_bar->clear();
									   _tl_bar->addActions( { saved_actions.begin(),
															  saved_actions.end() } );
									   disconnect( con );
								   } );
						  _tl_bar->clear();
						  _tl_bar->addAction( exit_action );
					  } ) } } } } } } };

	_init_toolbar(_actions_tree_root);

	setCentralWidget( _lst_wgt );

	add_alert( std::make_shared< alert >( alert::TYPE::INFO,
										  "a_alert",
										  "00-00-01",
										  "some_text",
										  "temperature sensor" ) );
	add_alert( std::make_shared< alert >( alert::TYPE::WARNING,
										  "c_alert",
										  "00-00-02",
										  "some_some_text",
										  "CO2 sensor" ) );
	add_alert( std::make_shared< alert >( alert::TYPE::ALARM,
										  "b_alert",
										  "00-00-03",
										  "some_some_some_text",
										  "light sensor" ) );

	// auto a = ( *_ngn_ptr )
	// 			 ->script( "return alert.new(alert.TYPE.INFO, 'hell', "
	// 					   "tostring(cascade_client.clock:now()), 'test "
	// 					   "text str ',' wowo ')" );

	// auto	   obj	 = make_lua_object_from_this();
	// sol::table table = obj.as< sol::table >();
	// table [ "add_alert" ]( this, a.get< alert >() );
}

void
alerts_page::add_alert( std::shared_ptr< alert > alert_ptr )
{
	if ( !std::any_of(
			 _alerts.begin(),
			 _alerts.end(),
			 [ alert_ptr ]( const auto& elem_ptr ) { return *elem_ptr == *alert_ptr; } ) )
		{
			_alerts.push_back( alert_ptr );
			sort_alerts();
			_update_list_widget();
		}
	else
		{
			std::cout << "'aletist_name' and 'alert_name' is not a unique pair";
		} // TODO! change this cout str to more consistent
}

void
alerts_page::remove_alert( const std::string& alert_name,
						   const std::string& alertist_name )
{
	auto it{ std::find_if( _alerts.begin(), _alerts.end(), [ & ]( const auto& elem ) {
		return elem->get_name() == alert_name
		   and elem->get_alertist_name() == alertist_name;
	} ) };

	if ( it != _alerts.end() )
		{
			_alerts.erase( it );
			sort_alerts();
		}
}

void
alerts_page::sort_alerts( std::optional< comparator > cmpr_opt )
{
	if ( cmpr_opt )
		{
			_lst_wgt->setProperty( "default_cmpr", QVariant::fromValue( *cmpr_opt ) );
		}
	else if ( auto v{ _lst_wgt->property( "default_cmpr" ) }; v.isValid() )
		{
			cmpr_opt = v.value< comparator >();
		}
	else { cmpr_opt = compare_by_date; }

	std::sort( _alerts.begin(),
			   _alerts.end(),
			   [ cmpr = *cmpr_opt ]( const auto& lhs, const auto& rhs ) {
				   return cmpr( *lhs, *rhs );
			   } );

	_update_list_widget();
}

void
alerts_page::_update_list_widget()
{
	_lst_wgt->clear();
	for ( const auto& alert_ptr : _alerts )
		{
			auto frame = new QFrame();
			frame->setFrameShape( QFrame::StyledPanel );
			frame->setMinimumHeight( 100 ); // Увеличили высоту для всех данных

			// Устанавливаем стиль в зависимости от типа alert
			QString styleSheet;
			switch ( alert_ptr->get_type() )
				{
					case alert::TYPE::INFO :
						styleSheet = "background:rgb(0, 29, 97); color: white;";
						break;
					case alert::TYPE::WARNING :
						styleSheet = "background:rgb(121, 117, 0); color: white;";
						break;
					case alert::TYPE::ALARM :
						styleSheet = "background:rgb(102, 14, 0); color: white;";
						break;
				}
			frame->setStyleSheet( styleSheet );

			auto mainLayout = new QVBoxLayout( frame );
			mainLayout->setContentsMargins( 10, 10, 10, 10 );
			mainLayout->setSpacing( 8 );

			auto	headerLayout = new QHBoxLayout();

			QLabel* typeIcon	 = new QLabel();
			QString iconPath;
			switch ( alert_ptr->get_type() )
				{
					case alert::TYPE::INFO :
						iconPath = ":alerts_page/icons/info.png";
						break;
					case alert::TYPE::WARNING :
						iconPath = ":alerts_page/icons/warning.png";
						break;
					case alert::TYPE::ALARM :
						iconPath = ":alerts_page/icons/alarm.png";
						break;
				}
			typeIcon->setPixmap( QPixmap( iconPath ).scaled( 20, 20 ) );
			headerLayout->addWidget( typeIcon );

			auto nameLabel = new QLabel(
				QString( "<b>%1</b>" )
					.arg( QString::fromStdString( alert_ptr->get_name() ) ) );
			nameLabel->setStyleSheet( "font-size: 12pt;" );
			headerLayout->addWidget( nameLabel );

			headerLayout->addStretch();

			auto timeLabel
				= new QLabel( QString::fromStdString( alert_ptr->get_timepoint() ) );
			timeLabel->setStyleSheet( "font-size: 10pt;" );
			headerLayout->addWidget( timeLabel );

			mainLayout->addLayout( headerLayout );

			auto textLabel
				= new QLabel( QString::fromStdString( alert_ptr->get_text() ) );
			textLabel->setWordWrap( true );
			textLabel->setStyleSheet( "font-size: 11pt; margin-top: 5px;" );
			mainLayout->addWidget( textLabel );

			auto alertistLabel = new QLabel(
				QString( "Alertist: %1" )
					.arg( QString::fromStdString( alert_ptr->get_alertist_name() ) ) );
			alertistLabel->setStyleSheet(
				"font-size: 10pt; font-style: italic; margin-top: 5px;" );
			mainLayout->addWidget( alertistLabel );

			if ( !alert_ptr->get_tags().empty() )
				{
					auto tagsLayout = new QHBoxLayout();
					tagsLayout->addWidget( new QLabel( "Tags:" ) );

					for ( const auto& tag : alert_ptr->get_tags() )
						{
							auto tagLabel = new QLabel( QString::fromStdString( tag ) );
							tagLabel->setStyleSheet( "background: rgba(255,255,255,0.2);"
													 "border-radius: 3px;"
													 "padding: 2px 5px;"
													 "margin-right: 5px;" );
							tagsLayout->addWidget( tagLabel );
						}

					tagsLayout->addStretch();
					mainLayout->addLayout( tagsLayout );
				}

			auto item = new QListWidgetItem();
			item->setSizeHint(
				QSize( frame->sizeHint().width(), frame->sizeHint().height() + 10 ) );
			item->setData( Qt::UserRole,
						   QString::fromStdString( alert_ptr->get_name() ) );

			_lst_wgt->addItem( item );
			_lst_wgt->setItemWidget( item, frame );
			_lst_wgt->scrollToItem( item );
			frame->setProperty( "alert_ptr", QVariant::fromValue( alert_ptr ) );
		}
}

std::vector< sol::object >
alerts_page::get_alerts()
{
	std::vector< sol::object > tmp;
	for ( const auto& elem : _alerts )
		{
			tmp.push_back( elem->make_lua_object_from_this() );
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
			type [ "sort_alerts" ]
				= &alerts_page::sort_alerts; // TODO! is it possible to pass lua function
											 // to sort std::shared_ptr<alert>?
		}
	std::cout << _class_name << "\t is registered" << std::endl;
}
