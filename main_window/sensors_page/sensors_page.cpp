#include "sensors_page.hpp"

#include <iostream>

sensors_page::sensors_page(QWidget* parent)
	: QMainWindow{parent}
{
	Q_INIT_RESOURCE(sp_icons); //dont forget to use different qrc file names in different folders
	// TODO refactor code to use only stylesheets for appearence settings
	_snsrs_grd->setSpacing(5);
	_snsrs_grd->setContentsMargins(5, 5, 5, 5);
	_snsrs_pln->setLayout(_snsrs_grd);
	_scrl_area->setWidgetResizable(true);
	_scrl_area->setWidget(_snsrs_pln);

	_tl_bar->setIconSize({32, 32});
	_tl_bar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	for(std::string action_str: {"add", "remove"})
	{
		auto path_str{":/sp/icons/" + action_str + ".png"};
		auto tmp_action{_tl_bar->addAction(
			QIcon(QPixmap{{path_str.c_str()}}.scaled({32, 32}, Qt::AspectRatioMode::KeepAspectRatio)),
			{action_str.c_str()})};
		std::cout << path_str << QIcon(QPixmap{{path_str.c_str()}}).isNull() << std::endl;
	}

	setCentralWidget(_scrl_area);
	addToolBar(Qt::TopToolBarArea, _tl_bar);

	// for(std::string action_str: {"sensors", "connections", "journal", "information", "settings"})
	// {
	// 	auto  path_str = ":/mw/icons/" + action_str + ".png";
	// 	QIcon icon(QPixmap(path_str.c_str()));
	// 	if(icon.isNull()) { std::cerr << "Ошибка: иконка не найдена: " << path_str << std::endl; }
	// 	else { std::cout << "Иконка загружена: " << path_str << std::endl; }
	// 	auto tmp_action = _tl_bar->addAction(icon, action_str.c_str());
	// }

}

void
sensors_page::addWidget()
{
	auto new_snsr{new QPushButton(_snsrs_pln)};
	auto count{_snsrs_grd->count()};
	new_snsr->setText("Виджет " + QString::number(count));
	new_snsr->setFixedSize(100, 50);

	int row{count / 2};
	int col{count % 2};

	// Добавляем виджет в сетку
	_snsrs_grd->addWidget(new_snsr, row, col);
}
