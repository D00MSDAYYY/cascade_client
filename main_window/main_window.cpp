#include "main_window.hpp"

#include "sensors_page.hpp"
#include "alerts_page.hpp"
#include "connections_page.hpp"
#include "logbook_page.hpp"
#include "charts_page.hpp"
#include "scenarios_page.hpp"
#include "script_area.hpp"

main_window::main_window(QWidget* parent)
	: QMainWindow(parent)
{
	Q_INIT_RESOURCE(mw_icons);

	_tl_bar->setIconSize({32, 32});
	_tl_bar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	_tl_bar->setMovable(false);

	for(int index{
			0
	 };
		const auto& [str, page]:
		std::vector<std::pair<std::string, QWidget*>>{{"alerts", new alerts_page{this}},
													  {"sensors", new sensors_page{this}},
													  {"connections", new connections_page{this}},
													  {"logbook", new logbook_page{this}},
													  {"charts", new charts_page{this}},
													  {"scripts", new scenarios_page{this}},
													  {"settings", new QWidget{this}}})
	{
		auto path_str{":/mw_icons/" + str + ".png"};
		auto action{_tl_bar->addAction(
			QIcon(QPixmap{{path_str.c_str()}}.scaled(_tl_bar->iconSize(),
													 Qt::AspectRatioMode::KeepAspectRatio)),
			{str.c_str()})};

		_stkd_wgt->insertWidget(index, page);
		QObject::connect(action, &QAction::triggered, [this, index]() { _stkd_wgt->setCurrentIndex(index); });
		++index;
	}
	addToolBar(Qt::LeftToolBarArea, _tl_bar);
	setCentralWidget(_stkd_wgt);
}

main_window::~main_window() {}
