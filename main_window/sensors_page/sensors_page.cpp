#include "sensors_page.hpp"

#include <QComboBox>
#include <QMessageBox>
#include <iostream>
#include <QInputDialog>

sensors_page::sensors_page(QWidget* parent)
	: QMainWindow{parent}
{
	Q_INIT_RESOURCE(sp_icons);

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

	for(const auto& [action_str, func]: std::vector<std::pair<std::string, void (sensors_page::*)()>>{
			{"add",	&sensors_page::addWidget	},
			{"remove", &sensors_page::removeWidget}
	   })
	{
		auto path_str{":/sp/icons/" + action_str + ".png"};
		auto action{_tl_bar->addAction(
			QIcon(QPixmap(path_str.c_str()).scaled({32, 32}, Qt::AspectRatioMode::KeepAspectRatio)),
			action_str.c_str())};
		connect(action, &QAction::triggered, this, func);
	}

	setCentralWidget(_scrl_area);

	addToolBar(Qt::TopToolBarArea, _tl_bar);
}

void
sensors_page::addWidget()
{
	auto new_snsr{new QPushButton(_snsrs_pln)};
	new_snsr->setMinimumSize({200, 100});
	auto count{_snsrs_grd->count()};
	new_snsr->setText("Виджет " + QString::number(count));

	// Устанавливаем политику изменения размеров
	new_snsr->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

	// Определяем позицию в сетке
	int row = count / 2;  // Два виджета в ряду
	int col = count % 2;

	// Добавляем виджет в сетку
	_snsrs_grd->addWidget(new_snsr, row, col);

	// Обновляем растяжение для строк
	_snsrs_grd->setRowStretch(row, 1);
}

void
sensors_page::removeWidget()
{
	// if(auto count{_snsrs_grd->count()}; count == 0) { return; }
	// else
	// {
	// 	if(auto item{_snsrs_grd->itemAt(count - 1)}; item)
	// 	{
	// 		if(auto widget{item->widget()}; widget)
	// 		{
	// 			_snsrs_grd->removeWidget(widget);

	// 			delete widget;
	// 			_snsrs_pln->adjustSize();
	// 		}
	// 	}
	// }
	// ////////////////////////////////////////////////////////////////////////////////////
	// int count = _snsrs_grd->count();
	// if(count == 0) { return; }

	// // Создаем диалоговое окно для выбора виджета
	// QComboBox* comboBox = new QComboBox();

	// // Добавляем виджеты в выпадающий список
	// for(int i = 0; i < count; ++i)
	// {
	// 	if(auto item = _snsrs_grd->itemAt(i))
	// 	{
	// 		if(auto widget = item->widget())
	// 		{
	// 			comboBox->addItem(widget->objectName(), QVariant::fromValue(widget));
	// 		}
	// 	}
	// }

	// // Показываем диалоговое окно
	// QMessageBox msgBox;
	// msgBox.setWindowTitle("Выберите виджет для удаления");
	// msgBox.setText("Выберите виджет, который вы хотите удалить:");
	// msgBox.setInformativeText("Выберите виджет для удаления:");
	// msgBox.setSizeGripEnabled(true);
	// msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	// msgBox.setDefaultButton(QMessageBox::Cancel);
	// msgBox.layout()->addWidget(comboBox);

	// if(msgBox.exec() == QMessageBox::Ok)
	// {
	// 	// Получаем выбранный виджет
	// 	QWidget* selectedWidget = comboBox->currentData().value<QWidget*>();
	// 	if(selectedWidget)
	// 	{
	// 		_snsrs_grd->removeWidget(selectedWidget);
	// 		delete selectedWidget;
	// 		_snsrs_pln->adjustSize();
	// 	}
	// }

	// // Освобождаем память
	// delete comboBox;
	// //////////////////////////////////////////////////////////////////////

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

	// Отображаем диалог с выбором виджета
	bool	ok;
	QString selectedWidgetText = QInputDialog::getItem(this,				// Родительский виджет
													   "Удаление виджета",	// Заголовок диалога
													   "Выберите виджет для удаления:",	 // Текст подсказки
													   widgetNames,						 // Список виджетов
													   0,	   // Индекс выбранного элемента по умолчанию
													   false,  // Редактируемый список
													   &ok	   // Флаг успешного выбора
	);

	// Если пользователь нажал "Отмена" или не выбрал виджет, выходим
	if(!ok || selectedWidgetText.isEmpty()) { return; }

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
}
