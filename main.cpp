#include "application.hpp"

int
main( int argc, char** argv )
{
	auto app{
	  application{ argc, argv }
	};

	return app.exec();
}

