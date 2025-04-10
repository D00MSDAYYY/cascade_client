#include "settings_page.hpp"

settings_page::settings_page( const std::string&  name,
							  script::engine::ptr ngn_ptr,
							  QWidget*			  parent )
	: QMainWindow( parent )
	, script::object{ name, ngn_ptr }
{
}
