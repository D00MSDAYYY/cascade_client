#include "sensors_page.hpp"

#include "sensors_creator.hpp"

#include <QInputDialog>
#include <QMessageBox>

sensors_page::sensors_page( const std::string&	name,
							scripting::engine::ptr ngn_ptr,
							QWidget*			parent )
	: page{name, ngn_ptr, parent}
{
	Q_INIT_RESOURCE( sensors_page );

	_tl_bar	   = new QToolBar{ "Tool bar", this };
	_snsrs_grd = new QGridLayout{};
	_snsrs_pln = new QWidget{ this };
	_scrl_area = new QScrollArea{ this };

	_snsrs_grd->setSpacing( 5 );
	_snsrs_grd->setContentsMargins( 5, 5, 5, 5 );

	_snsrs_grd->setColumnStretch( 0, 1 );
	_snsrs_grd->setColumnStretch( 1, 1 );

	_snsrs_grd->setRowStretch( 0, 1 );
	_snsrs_grd->setRowStretch( 1, 1 );

	_snsrs_pln->setLayout( _snsrs_grd );

	_scrl_area->setWidgetResizable( true );
	_scrl_area->setWidget( _snsrs_pln );

	_tl_bar->setIconSize( { 32, 32 } );
	_tl_bar->setToolButtonStyle( Qt::ToolButtonTextUnderIcon );
	_tl_bar->setMovable( false );

	for ( const auto& [ str, func ] :
		  std::vector< std::pair< std::string, std::function< void() > > >{
			{ "filter", []() { return; } },
			{ "|", []() { return; } },
			{ "add", std::bind( &sensors_page::addSensor, this ) },
			{ "remove", std::bind( &sensors_page::removeSensor, this ) },
			{ "select", []() { return; } },
			{ "|", []() { return; } },
			{ "resume", []() { return; } },
			{ "suspend", []() { return; } }
	} )
		{
			if ( str == "|" ) { _tl_bar->addSeparator(); }
			else
				{
					auto path{ ":/sensors_page/icons/" + str + ".png" };
					auto action{ _tl_bar->addAction(
						QIcon{ QPixmap{ path.c_str() }.scaled(
							_tl_bar->iconSize(),
							Qt::AspectRatioMode::KeepAspectRatio ) },
						str.c_str() ) };
					connect( action, &QAction::triggered, this, func );
				}
		}

	setCentralWidget( _scrl_area );

	addToolBar( Qt::TopToolBarArea, _tl_bar );
	register_in_lua(*_ngn_ptr);
}

sensors_page::~sensors_page() { Q_CLEANUP_RESOURCE( sensors_page ); }

void
sensors_page::addSensor()
{
	auto creator{ new sensors_creator{ this } };

	connect( creator,
			 &sensors_creator::sensorCreated,
			 this,
			 [ this ]( QWidget* new_snsr ) {
				 new_snsr->setStyleSheet( "background-color: gray ;" );

				 new_snsr->setMinimumSize( 200, 100 );

				 auto count{ _snsrs_grd->count() };
				 new_snsr->setObjectName( "Виджет " + QString::number( count ) );

				 new_snsr->setSizePolicy( QSizePolicy::Expanding,
										  QSizePolicy::Expanding );

				 int row = count / 2;
				 int col = count % 2;

				 _snsrs_grd->addWidget( new_snsr, row, col );


				 _snsrs_grd->setRowStretch( row, 1 );
			 } );
	creator->exec();
}

void
sensors_page::removeSensor()
{
	int count = _snsrs_grd->count();

	if ( count == 0 )
		{
			QMessageBox::information( this, "Информация", "Нет виджетов для удаления." );
			return;
		}

	QStringList widgetNames;
	for ( int i = 0; i < count; ++i )
		{
			QLayoutItem* item = _snsrs_grd->itemAt( i );
			if ( item && item->widget() )
				{
					widgetNames.append( item->widget()->objectName() );
				}
		}

	QInputDialog dialog( this );
	dialog.setWindowTitle( "Удаление виджета" );
	dialog.setLabelText( "Выберите виджет для удаления:" );
	dialog.setComboBoxItems( widgetNames );
	dialog.setComboBoxEditable( false );
	dialog.setWindowFlags( dialog.windowFlags() & ~Qt::WindowCloseButtonHint );

	if ( dialog.exec() != QDialog::Accepted ) { return; }

	auto selectedWidgetText = dialog.textValue();

	for ( int i = 0; i < count; ++i )
		{
			QLayoutItem* item = _snsrs_grd->itemAt( i );
			if ( item && item->widget()
				 && item->widget()->objectName() == selectedWidgetText )
				{
					QWidget* widget = item->widget();

					_snsrs_grd->removeWidget( widget );

					delete widget;

					_snsrs_pln->adjustSize();
					break;
				}
		}
	_redistributeWidgets();
}



void
sensors_page::register_in_lua(const scripting::engine::ptr& ngn_ptr)
{
	if ( can_register_in_lua<sensors_page>(ngn_ptr) )
		{
			auto type{ ngn_ptr->new_usertype< sensors_page >( _class_name,
															   sol::base_classes,
															   sol::bases< page >() ) };
		}
	std::cout << _class_name << "\t is registered" << std::endl;
}

void
sensors_page::_redistributeWidgets()
{
	QList< QWidget* > widgets;
	for ( int i = 0; i < _snsrs_grd->count(); ++i )
		{
			QLayoutItem* item = _snsrs_grd->itemAt( i );
			if ( item && item->widget() ) { widgets.append( item->widget() ); }
		}
	while ( _snsrs_grd->count() > 0 )
		{
			QLayoutItem* item = _snsrs_grd->takeAt( 0 );
			if ( item && item->widget() ) { _snsrs_grd->removeWidget( item->widget() ); }
			delete item;
		}
	for ( int i = 0; i < widgets.size(); ++i )
		{
			int row = i / 2;
			int col = i % 2;
			_snsrs_grd->addWidget( widgets [ i ], row, col );
		}
	for ( int row = 0; row <= widgets.size() / 2; ++row )
		{
			_snsrs_grd->setRowStretch( row, 1 );
		}
}
