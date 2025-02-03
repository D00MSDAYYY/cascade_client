#include "main_window.hpp"

#include "sensors_page.hpp"

main_window::main_window(QWidget* parent)
	: QMainWindow(parent)
{
	Q_INIT_RESOURCE(mw_icons);

	_tl_bar->setIconSize({32, 32});
	_tl_bar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	for(std::string action_str: {"sensors", "connections", "journal", "information", "settings"})
	{
		// TODO dont forget to inset something like this in for stmt
		// std::vector<std::pair<std::string, void (sensors_page::*)()>> tmp{
		// 	{"add",	&sensors_page::addWidget	},
		// 	{"remove", &sensors_page::removeWidget}
		//    };
		auto path_str{":/icons/" + action_str + ".png"};
		_tl_bar->addAction(
			QIcon(QPixmap{{path_str.c_str()}}.scaled({32, 32}, Qt::AspectRatioMode::KeepAspectRatio)),
			{action_str.c_str()});
	}
	addToolBar(Qt::LeftToolBarArea, _tl_bar);

	setCentralWidget(_stkd_wgt);

	for(int index1{0}; auto& action: _tl_bar->actions())
	{
		auto page{new QWidget{}};
		if(index1 == 0)
		{
			delete page;
			page = new sensors_page{};
		}
		else
		{
			page->setStyleSheet("background-color: black ;");

			QString color = index1 == 0 ? "blue"
						  : index1 == 1 ? "red"
						  : index1 == 2 ? "yellow"
						  : index1 == 3 ? "green"
										: "magenta";
			page->setStyleSheet("background-color: " + color + ";");
		}
		_stkd_wgt->insertWidget(index1, page);
		QObject::connect(action,
						 &QAction::triggered,
						 [this, index1]() { _stkd_wgt->setCurrentIndex(index1); });

		++index1;
	}
}

main_window::~main_window() {}
