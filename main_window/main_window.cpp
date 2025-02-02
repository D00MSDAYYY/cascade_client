#include "main_window.hpp"

#include <vector>
#include <string>


main_window::main_window(QWidget* parent)
	: QMainWindow(parent)
{
	Q_INIT_RESOURCE(icons);


	_tb->setIconSize({32, 32});
	_tb->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

	for(std::string action_str: {"sensors", "connections", "journal", "information", "settings"})
	{
		auto path_str{":/icons/" + action_str + ".png"};
		auto tmp_action{
			_tb->addAction(QIcon(QPixmap{{path_str.c_str()}}.scaled({32, 32}, Qt::AspectRatioMode::KeepAspectRatio)),
						   {action_str.c_str()})};
	}
	addToolBar(_tb);
	


	
}

main_window::~main_window() {}
