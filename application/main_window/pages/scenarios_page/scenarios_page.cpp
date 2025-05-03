
#include "scenarios_page.hpp"

#include <QInputDialog>
#include <QMessageBox>

scenarios_page::scenarios_page( const std::string& name, scripting::engine::ptr ngn_ptr, QWidget* parent )
	: page{ name, ngn_ptr, parent }
{
	Q_INIT_RESOURCE( scenarios_page );
	register_in_lua( *_ngn_ptr );

	_lst_wgt = new QListWidget{ this };

	_nd_t _actions_tree_root{
		{ .name		   = "_root_node",
		  .description = "don't use this node ",
		  .children	   = { _nd_t{ { .name = "sort" } },
						   _nd_t{ {
							 .name = "|",
						   } },
						   _nd_t{ { .name = "add" } },
						   _nd_t{ { .name = "remove" } },
						   _nd_t{ { .name = "|" } },
						   _nd_t{ { .name = "suspend" } },
						   _nd_t{ { .name = "resume" } } } }
	};

	_init_toolbar( _actions_tree_root );

	setCentralWidget( _lst_wgt );
}

scenarios_page::~scenarios_page() { Q_CLEANUP_RESOURCE( scenarios_page ); }

void
scenarios_page::register_in_lua( const scripting::engine::ptr& ngn_ptr )
{
	if ( can_register_in_lua< scenarios_page >( ngn_ptr ) )
		{
			auto type{ ngn_ptr->new_usertype< scenarios_page >( _class_name,
																sol::base_classes,
																sol::bases< page >() ) };
		}
	std::cout << _class_name << "\t is registered" << std::endl;
}
