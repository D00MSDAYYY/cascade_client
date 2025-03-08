#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

class script_engine
{
public:
	script_engine();
	script_engine( script_engine& se ) = delete;

	void		add_object( const std::string& name,
							sol::table		   object ); //	or register_object();
	void		remove_object();
	void		do_code_globally( std::string script );
	void		do_code_separately( std::string script );
	std::string _get_stack_dump();

private:
};
