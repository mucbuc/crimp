#include <string>
#include <exception> 

#include "test.h"

int main(int argc, const char * argv[])
{
	using namespace std;
	string a( "hello" ); 

	ASSERT( !a.empty() )( a )( a.size() );

	return 0; 
}