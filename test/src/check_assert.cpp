#include <string>

#include "test.h"

int main(int argc, const char * argv[])
{
	using namespace std;
	string a( "hello" ); 

	ASSERT( !a.empty() )( a );

	return 0; 
}