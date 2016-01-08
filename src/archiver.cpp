#include <fstream>

#include "archiver.h"



namespace private_assert
{
	archiver & archiver::instance()
	{
		static archiver local;
		return local;
	}

	archiver::~archiver()
	{
		std::fstream out( "test_result.json", std::fstream::out );

		out << "{\n";
		out << "\"passed\": " << passed << std::endl;
		out << "}\n";
	}

	void archiver::pass()
	{
		++passed;
	}

	void archiver::fail( 
		const char * file, 
		int line, 
        const char * function, 
        const char * message )
	{

	}
}	// private_assert