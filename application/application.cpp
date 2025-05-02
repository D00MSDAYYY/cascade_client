#include "application.hpp"

#include <QFile>

application::application( int& argc, char** argv )
	: QApplication{ argc, argv }
	, scripting::object{ scripting::engine::make_real_engine() }
{
	Q_INIT_RESOURCE( application );
	setStyle( "Fusion" );

	( *_ngn_ptr )->open_libraries( sol::lib::base, sol::lib::table, sol::lib::string );


	if ( QFile file( ":/application/scripts/aux_functions.lua" );
		 file.open( QIODevice::ReadOnly | QIODevice::Text ) )
		{
			QTextStream in{ &file };
			auto		str{ in.readAll().toStdString() };
			( *_ngn_ptr )->script( str );
			file.close();
		}
	else
		{
			std::cout << "can't open file aux_functions.lua" << std::endl;
		}

	register_in_lua( *_ngn_ptr );

	( *_ngn_ptr )->globals() [ "cascade_client" ] = this;

	_clock	  = std::shared_ptr< class clock >( new class clock{ *_ngn_ptr } );

	_mn_wndw  = std::shared_ptr< main_window >( new main_window{ *_ngn_ptr } );

	_dbg_wndw = std::shared_ptr< debug_console >( new debug_console{ *_ngn_ptr } );


	_mn_wndw->show();
	_dbg_wndw->show();

	_mn_wndw->resize( 1'000, 800 );
	_mn_wndw->setMinimumSize( 800, 600 );

	_dbg_wndw->resize( 500, 400 );
	_dbg_wndw->setMinimumSize( 400, 300 );
}

application::~application() { Q_CLEANUP_RESOURCE( application ); }

void
application::register_in_lua( const scripting::engine::ptr& ngn_ptr )
{
	if ( can_register_in_lua< application >( ngn_ptr ) )
		{
			auto type{ ngn_ptr->new_usertype< application >( _class_name ) };
			type [ "main_window" ] = &application::_mn_wndw;
			type [ "clock" ]	   = &application::_clock;
		}
	std::cout << _class_name << "\t is registered" << std::endl;
}
