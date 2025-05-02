#include "charts_page.hpp"

charts_page::charts_page( const std::string&		   name,
						  const scripting::engine::ptr ngn_ptr,
						  QWidget*					   parent )
	: page{ name, ngn_ptr, parent }
{
	Q_INIT_RESOURCE( charts_page );
	register_in_lua( *_ngn_ptr );

	_lst_wgt		   = new QListWidget{ this };
	
	using _nd_t		   = page::_nd_t;
	_actions_tree_root = std::make_shared< _nd_t >( _nd_t{
	  { .name		 = "_root_node",
		.description = "don't use this node ",
		.children	 = { _nd_t{ { .name = "sort" } },
						 _nd_t{ {
						   .name = "|",
						 } },
						 _nd_t{ { .name = "add" } },
						 _nd_t{ { .name = "remove" } },
						 _nd_t{ { .name = "|" } },
						 _nd_t{ { .name = "suspend" } },
						 _nd_t{ { .name = "resume" } } } }
	} );

	_init_toolbar();

	setCentralWidget( _lst_wgt );
}

charts_page::~charts_page() { Q_CLEANUP_RESOURCE( charts_page ); }

void
charts_page::register_in_lua( const scripting::engine::ptr& ngn_ptr )
{
	if ( can_register_in_lua< charts_page >( ngn_ptr ) )
		{
			auto type{ ngn_ptr->new_usertype< charts_page >( _class_name,
															 sol::base_classes,
															 sol::bases< page >() ) };
		}
	std::cout << _class_name << "\t is registered" << std::endl;
}

