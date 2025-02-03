#include "sensors_page.hpp"

#include <iostream>

sensors_page::sensors_page(QWidget* parent)
	: QMainWindow{parent}
{
	Q_INIT_RESOURCE(sp_icons);	// dont forget to use different qrc file names in different folders
	// TODO refactor code to use only stylesheets for appearence settings
	_snsrs_grd->setSpacing(5);
	_snsrs_grd->setContentsMargins(5, 5, 5, 5);
	_snsrs_pln->setLayout(_snsrs_grd);
	_scrl_area->setWidgetResizable(true);
	_scrl_area->setWidget(_snsrs_pln);

	_tl_bar->setIconSize({32, 32});
	_tl_bar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	for(std::vector<std::pair<std::string, void (sensors_page::*)()>> str_func{
			{"add",	&sensors_page::addWidget	},
			{"remove", &sensors_page::removeWidget}
	   };
		const auto [str, func]: str_func)
	{
		auto path_str{":/sp/icons/" + str + ".png"};
		auto action{_tl_bar->addAction(
			QIcon(QPixmap{{path_str.c_str()}}.scaled({32, 32}, Qt::AspectRatioMode::KeepAspectRatio)),
			{str.c_str()})};

		QObject::connect(action, &QAction::triggered, [this, func]() { (this->*func)(); });
	}

	setCentralWidget(_scrl_area);
	addToolBar(Qt::TopToolBarArea, _tl_bar);
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

	_snsrs_grd->addWidget(new_snsr, row, col);
}

void
sensors_page::removeWidget()
{
	if(auto count{_snsrs_grd->count()}; count == 0) { return; }
	else
	{
		if(auto item{_snsrs_grd->itemAt(count - 1)}; item)
		{
			if(auto widget{item->widget()}; widget)
			{
				_snsrs_grd->removeWidget(widget);

				delete widget;
				_snsrs_pln->adjustSize();
			}
		}
	}
}
