#include <iostream>

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

	cout << var << endl;
	return 0; 
}
