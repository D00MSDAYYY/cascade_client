
#include "connections_page.hpp"

#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>

connections_page::connections_page( const std::string&	name,
									scripting::engine::ptr ngn_ptr,
									QWidget*			parent )
	: page{name, ngn_ptr, parent}
{
	Q_INIT_RESOURCE( connections_page );
	_snsrs_grd = new QGridLayout{};
	_snsrs_pln = new QWidget{ this };
	_scrl_area = new QScrollArea{ this };
	_tl_bar	   = new QToolBar{ "Tool bar", this };

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
			{ "add", std::bind( &connections_page::addConnection, this ) },
			{ "remove", std::bind( &connections_page::removeConnection, this ) },
			{ "select", []() { return; } },
			{ "|", []() { return; } },
			{ "resume", []() { return; } },
			{ "suspend", []() { return; } }
	} )
		{
			if ( str == "|" ) { _tl_bar->addSeparator(); }
			else
				{
					auto path{ ":/connections_page/icons/" + str + ".png" };
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

void
connections_page::addConnection()
{
	
}

void
connections_page::removeConnection()
{
	// Получаем количество виджетов в сетке
	int count = _snsrs_grd->count();

	// Если виджетов нет, выходим
	if ( count == 0 )
		{
			QMessageBox::information( this, "Информация", "Нет виджетов для удаления." );
			return;
		}

	// Создаем список текстов виджетов
	QStringList widgetNames;
	for ( int i = 0; i < count; ++i )
		{
			QLayoutItem* item = _snsrs_grd->itemAt( i );
			if ( item && item->widget() )
				{
					widgetNames.append( item->widget()->objectName() );
				}
		}

	// Создаем диалоговое окно для выбора виджета
	QInputDialog dialog( this );
	dialog.setWindowTitle( "Удаление виджета" );
	dialog.setLabelText( "Выберите виджет для удаления:" );
	dialog.setComboBoxItems( widgetNames );
	dialog.setComboBoxEditable( false );
	dialog.setWindowFlags( dialog.windowFlags()
						   & ~Qt::WindowCloseButtonHint ); // Убираем кнопку закрытия

	// Отображаем диалог с выбором виджета
	if ( dialog.exec() != QDialog::Accepted )
		{
			return; // Если пользователь нажал "Cancel" или закрыл окно, выходим
		}

	QString selectedWidgetText = dialog.textValue();

	// Ищем выбранный виджет и удаляем его
	for ( int i = 0; i < count; ++i )
		{
			QLayoutItem* item = _snsrs_grd->itemAt( i );
			if ( item && item->widget()
				 && item->widget()->objectName() == selectedWidgetText )
				{
					QWidget* widget = item->widget();

					// Удаляем виджет из сетки
					_snsrs_grd->removeWidget( widget );

					// Освобождаем память
					delete widget;

					// Обновляем содержимое прокручиваемой области
					_snsrs_pln->adjustSize();
					break;
				}
		}

	// Перераспределяем оставшиеся виджеты
	_redistributeWidgets();
}



void
connections_page::register_in_lua(const scripting::engine::ptr& ngn_ptr)
{
	if ( can_register_in_lua<connections_page>(ngn_ptr) )
		{
			auto type{ ngn_ptr->new_usertype< connections_page >(
				_class_name,
				sol::base_classes,
				sol::bases< page >() ) };
		}
}

void
connections_page::_redistributeWidgets()
{
	QList< QWidget* > widgets;
	for ( int i = 0; i < _snsrs_grd->count(); ++i )
		{
			QLayoutItem* item = _snsrs_grd->itemAt( i );
			if ( item && item->widget() ) { widgets.append( item->widget() ); }
		}

	// Очищаем сетку
	while ( _snsrs_grd->count() > 0 )
		{
			QLayoutItem* item = _snsrs_grd->takeAt( 0 );
			if ( item && item->widget() ) { _snsrs_grd->removeWidget( item->widget() ); }
			delete item;
		}

	// Добавляем виджеты заново
	for ( int i = 0; i < widgets.size(); ++i )
		{
			int row = i / 2; // Два виджета в ряду
			int col = i % 2;
			_snsrs_grd->addWidget( widgets [ i ], row, col );
		}

	// Обновляем растяжение для строк
	for ( int row = 0; row <= widgets.size() / 2; ++row )
		{
			_snsrs_grd->setRowStretch( row, 1 );
		}
}
