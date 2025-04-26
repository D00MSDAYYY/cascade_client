#pragma once

#include "alert.hpp"
#include "page.hpp"

#include <QListWidget> // TODO! mb add _lst_wgt to base class (page) coz i use it so often std::optional<>?
#include <functional>
#include <vector>

class alerts_page : public page
{
	Q_OBJECT

public:
	alerts_page( const std::string&			  name,
				 const scripting::engine::ptr ngn_ptr,
				 QWidget*					  parent = nullptr );
	~alerts_page() = default;

	CLASS_NAME_AS_STRING( alerts_page )
	MAKE_LUA_OBJECT_FROM_THIS()
	STATIC_REGISTER_IN_LUA()


	std::vector< sol::object >
	get_alerts();
	// TODO! mb add alert id as return to unique identifing (to store into
	// alertist to faster and convinient deletion)

	void
	add_alert( std::shared_ptr<alert> alert_ptr );

	void
	remove_alert( const std::string& alert_name, const std::string& alertist_name );

	using comparator = std::function< bool( const alert& lhs, const alert& rhs ) >;
	void
	sort_alerts( std::optional< comparator > cmpr_opt = std::nullopt );

private:
	void
											_update_list_widget();

	QListWidget*							_lst_wgt{};
	std::vector< std::shared_ptr< alert > > _alerts;
};
