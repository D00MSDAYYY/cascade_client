#pragma once


#include "page.hpp"

#include <QListWidget>
#include <functional>
#include <vector>

//! #include "connection.hpp"
class connection;

class connections_page : public page
{
	Q_OBJECT

public:
	connections_page( const std::string&		   name,
					  const scripting::engine::ptr ngn_ptr,
					  QWidget*					   parent = nullptr );
	~connections_page() = default;

	CLASS_NAME_AS_STRING( connections_page )
	MAKE_LUA_OBJECT_FROM_THIS()
	STATIC_REGISTER_IN_LUA()

	std::vector< sol::object >
	get_connections();

	void
	add_connection();
	void
	remove_connection();

	using comparator
		= std::function< bool( const connection& lhs, const connection& rhs ) >;
	void
	sort_connections( std::optional< comparator > cmpr_opt = std::nullopt );

	void //!
	get_connections_creator();

private:
	void
				 _update_list_widget();

	QListWidget*							_lst_wgt{};
	std::vector< std::shared_ptr< connection > > _connections;
};
