#include "sensors_page.hpp"

#include "sensors_creator.hpp"

#include <QInputDialog>
#include <QMessageBox>


static sensors_page::comparator compare_by_name{ []( const sensor& lhs,
													 const sensor& rhs ) -> bool {
	return lhs.get_name() < rhs.get_name();
} };

sensors_page::sensors_page( const std::string&	   name,
							scripting::engine::ptr ngn_ptr,
							QWidget*			   parent )
	: page{ name, ngn_ptr, parent }
{
	Q_INIT_RESOURCE( sensors_page );
	register_in_lua( *_ngn_ptr );

	_lst_wgt		   = new QListWidget{ this };

	using _nd_t		   = page::_nd_t;
	_actions_tree_root = std::make_shared< _nd_t >( _nd_t{
	  { .name		 = "_root_node",
		.description = "don't use this node ",
		.children
		= { _nd_t{ { .name = "sort" } },
			_nd_t{ {
			  .name = "|",
			} },
			_nd_t{
			  { .name = "add",
				.data
				= { ._qaction = _bind_qaction_with_func(
						new QAction{ this },
						[ this ]( auto add_action ) {
							std::cout << "check" << std::endl;
							QList< QAction* > saved_actions{};
							for ( const auto& action_ptr : _tl_bar->actions() )
								{
									saved_actions.append( action_ptr );
								}

							auto exit_action{
								new QAction{
		  QIcon( QPixmap{
									std::string{ ":sensors_page/icons/exit.png" }
										.c_str() }
											 .scaled(
												 iconSize(),
		 Qt::AspectRatioMode::KeepAspectRatio ) ),
		  "exit", this }
							};
							connect( exit_action,
									 &QAction::triggered,
									 [ this, saved_actions ]() {
										 _tl_bar->clear();
										 _tl_bar->addActions( { saved_actions.begin(),
																saved_actions.end() } );
									 } );
							_tl_bar->clear();
							_tl_bar->addAction( exit_action );
							auto creator{ new sensors_creator{ this } };
							setCentralWidget( creator );
						} ) } } },
			_nd_t{
			  { .name = "remove",
				.data
				= { ._qaction = _bind_qaction_with_func(
						new QAction{ this },
						[ this ]( auto remove_action ) {
							auto con{ connect(
								_lst_wgt,
								&QListWidget::itemClicked,
								[ this ]( QListWidgetItem* item ) {
									if ( auto frame_ptr{ qobject_cast< QFrame* >(
											 _lst_wgt->itemWidget( item ) ) } )
										{
											auto sensor_ptr{
												frame_ptr->property( "sensor" )
													.value< std::shared_ptr< sensor > >()
											};
											remove_sensor( sensor_ptr->get_name() );
											sort_sensors();
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
									std::string{ ":sensors_page/icons/exit.png" }
										.c_str() }
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
						} ) } } },
			_nd_t{ { .name = "|" } },
			_nd_t{ { .name = "suspend" } },
			_nd_t{ { .name = "resume" } } } }
	  } );

	_init_toolbar();

	setCentralWidget( _lst_wgt );
}

sensors_page::~sensors_page() { Q_CLEANUP_RESOURCE( sensors_page ); }

void
sensors_page::add_sensor( std::shared_ptr< sensor > sensor_ptr )
{
	if ( !std::any_of( _sensors.begin(),
					   _sensors.end(),
					   [ sensor_ptr ]( const auto& elem_ptr ) {
						   return *elem_ptr == *sensor_ptr;
					   } ) )
		{
			_sensors.push_back( sensor_ptr );
			sort_sensors();
			_update_list_widget();
		}
	else
		{
			std::cout << "'sensor name' have to be unique";
		} // TODO! change this cout str to more consistent
}

void
sensors_page::remove_sensor( const std::string& sensor_name )
{
	auto it{ std::find_if( _sensors.begin(), _sensors.end(), [ & ]( const auto& elem ) {
		return elem->get_name() == sensor_name;
	} ) };

	if ( it != _sensors.end() ) { _sensors.erase( it ); }
}

void
sensors_page::sort_sensors( std::optional< comparator > cmpr_opt )
{
	if ( cmpr_opt )
		{
			_lst_wgt->setProperty( "default_cmpr", QVariant::fromValue( *cmpr_opt ) );
		}
	else if ( auto v{ _lst_wgt->property( "default_cmpr" ) }; v.isValid() )
		{
			cmpr_opt = v.value< comparator >();
		}
	else { cmpr_opt = compare_by_name; }

	std::sort( _sensors.begin(),
			   _sensors.end(),
			   [ cmpr = *cmpr_opt ]( const auto& lhs, const auto& rhs ) {
				   return cmpr( *lhs, *rhs );
			   } );

	_update_list_widget();
}

void
sensors_page::_update_list_widget()
{
	_lst_wgt->clear();
	for ( const auto& sensor_ptr : _sensors )
		{
			auto frame = new QFrame();
			frame->setFrameShape( QFrame::StyledPanel );
			frame->setMinimumHeight( 100 ); // Увеличили высоту для всех данных
		}
}

// void
// sensors_page::add_sensor()
// {
// 	auto creator{ new sensors_creator{ this } };

// 	connect( creator,
// 			 &sensors_creator::sensor_created,
// 			 this,
// 			 [ this ]( QWidget* new_snsr ) {
// 				 new_snsr->setStyleSheet( "background-color: gray ;" );

// 				 new_snsr->setMinimumSize( 200, 100 );

// 				 auto count{ _snsrs_grd->count() };
// 				 new_snsr->setObjectName( "Виджет " + QString::number( count ) );

// 				 new_snsr->setSizePolicy( QSizePolicy::Expanding,
// 										  QSizePolicy::Expanding );

// 				 int row = count / 2;
// 				 int col = count % 2;

// 				 _snsrs_grd->addWidget( new_snsr, row, col );


// 				 _snsrs_grd->setRowStretch( row, 1 );
// 			 } );
// 	creator->exec();
// }


void
sensors_page::register_in_lua( const scripting::engine::ptr& ngn_ptr )
{
	if ( can_register_in_lua< sensors_page >( ngn_ptr ) )
		{
			auto type{ ngn_ptr->new_usertype< sensors_page >( _class_name,
															  sol::base_classes,
															  sol::bases< page >() ) };
		}
	std::cout << _class_name << "\t is registered" << std::endl;
}


