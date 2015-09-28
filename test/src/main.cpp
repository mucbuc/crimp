#include <iostream>

//#include "test.h"

int main(int argc, const char * argv[])
{
	using namespace std;
	

#ifdef TARGET_TEST
	string var( "hello test" );
#elif 1
#ifndef NDEBUG
	string var( "hello debug" ); 
#else
	string var( "hello release" );
#endif
#endif	 
//	ASSERT( var.size() )(var);

	cout << var << endl;
	return 0; 
}
