
#include "connections_page.hpp"

#include <QInputDialog>
#include <QMessageBox>
#include <QPushButton>

connections_page::connections_page(QWidget* parent)
	: QMainWindow{parent}
{
	Q_INIT_RESOURCE(cn_icons);

	_snsrs_grd->setSpacing(5);
	_snsrs_grd->setContentsMargins(5, 5, 5, 5);

	_snsrs_grd->setColumnStretch(0, 1);
	_snsrs_grd->setColumnStretch(1, 1);

	_snsrs_grd->setRowStretch(0, 1);
	_snsrs_grd->setRowStretch(1, 1);

	_snsrs_pln->setLayout(_snsrs_grd);

	_scrl_area->setWidgetResizable(true);
	_scrl_area->setWidget(_snsrs_pln);

	_tl_bar->setIconSize({32, 32});
	_tl_bar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_tl_bar->setMovable(false);

	for(const auto& [str, func]:
		std::vector<std::pair<std::string, std::function<void()>>>{
			{"add", std::bind(&connections_page::addConnection, this)},
			{"remove", std::bind(&connections_page::removeConnection, this)},
			{"select", []() { return; }},
			{"|", []() { return; }},
			{"resume", []() { return; }},
			{"suspend", []() { return; }}
	 })
	{
		if(str == "|") { _tl_bar->addSeparator(); }
		else
		{
			auto path{":/cn_icons/" + str + ".png"};
			auto action{
				_tl_bar->addAction(QIcon{QPixmap{path.c_str()}.scaled(_tl_bar->iconSize(),
																	  Qt::AspectRatioMode::KeepAspectRatio)},
								   str.c_str())};
			connect(action, &QAction::triggered, this, func);
		}
	}

	setCentralWidget(_scrl_area);

	addToolBar(Qt::TopToolBarArea, _tl_bar);
}

void
connections_page::addConnection()
{
	// auto creator{new sensors_creator{this}};

	// connect(creator,
	// 		&sensors_creator::sensorCreated,
	// 		this,
	// 		[this](QWidget* new_snsr)
	// 		{
	// 			new_snsr->setStyleSheet("background-color: gray ;");

	// 			new_snsr->setMinimumSize(200, 100);

	// 			auto count{_snsrs_grd->count()};
	// 			new_snsr->setObjectName("Виджет " + QString::number(count));
	// 			// Устанавливаем политику изменения размеров
	// 			new_snsr->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	// 			// Определяем позицию в сетке
	// 			int row = count / 2;  // Два виджета в ряду
	// 			int col = count % 2;

	// 			// Добавляем виджет в сетку
	// 			_snsrs_grd->addWidget(new_snsr, row, col);

	// 			// Обновляем растяжение для строк
	// 			_snsrs_grd->setRowStretch(row, 1);
	// 		});
	// creator->exec();
}

void
connections_page::removeConnection()
{
	// Получаем количество виджетов в сетке
	int count = _snsrs_grd->count();

	// Если виджетов нет, выходим
	if(count == 0)
	{
		QMessageBox::information(this, "Информация", "Нет виджетов для удаления.");
		return;
	}

	// Создаем список текстов виджетов
	QStringList widgetNames;
	for(int i = 0; i < count; ++i)
	{
		QLayoutItem* item = _snsrs_grd->itemAt(i);
		if(item && item->widget()) { widgetNames.append(item->widget()->objectName()); }
	}

	// Создаем диалоговое окно для выбора виджета
	QInputDialog dialog(this);
	dialog.setWindowTitle("Удаление виджета");
	dialog.setLabelText("Выберите виджет для удаления:");
	dialog.setComboBoxItems(widgetNames);
	dialog.setComboBoxEditable(false);
	dialog.setWindowFlags(dialog.windowFlags() & ~Qt::WindowCloseButtonHint);  // Убираем кнопку закрытия

	// Отображаем диалог с выбором виджета
	if(dialog.exec() != QDialog::Accepted)
	{
		return;	 // Если пользователь нажал "Cancel" или закрыл окно, выходим
	}

	QString selectedWidgetText = dialog.textValue();

	// Ищем выбранный виджет и удаляем его
	for(int i = 0; i < count; ++i)
	{
		QLayoutItem* item = _snsrs_grd->itemAt(i);
		if(item && item->widget() && item->widget()->objectName() == selectedWidgetText)
		{
			QWidget* widget = item->widget();

			// Удаляем виджет из сетки
			_snsrs_grd->removeWidget(widget);

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
connections_page::_redistributeWidgets()
{
	// Собираем все виджеты из сетки
	QList<QWidget*> widgets;
	for(int i = 0; i < _snsrs_grd->count(); ++i)
	{
		QLayoutItem* item = _snsrs_grd->itemAt(i);
		if(item && item->widget()) { widgets.append(item->widget()); }
	}

	// Очищаем сетку
	while(_snsrs_grd->count() > 0)
	{
		QLayoutItem* item = _snsrs_grd->takeAt(0);
		if(item && item->widget()) { _snsrs_grd->removeWidget(item->widget()); }
		delete item;
	}

	// Добавляем виджеты заново
	for(int i = 0; i < widgets.size(); ++i)
	{
		int row = i / 2;  // Два виджета в ряду
		int col = i % 2;
		_snsrs_grd->addWidget(widgets[i], row, col);
	}

	// Обновляем растяжение для строк
	for(int row = 0; row <= widgets.size() / 2; ++row)
	{
		_snsrs_grd->setRowStretch(row, 1);
	}
}
