#include <iostream>

//#include "test.h"

int main(int argc, const char * argv[])
{
	using namespace std;
	

#ifdef TARGET_TEST
	string var( "hello test" );
#endif	 
//	ASSERT( var.size() )(var);

	cout << var << endl;
	return 0; 
}
