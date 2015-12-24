#include <iostream>

#include <src/data/content.json.h>

int main(int argc, const char * argv[])
{
	using namespace std;
	
<<<<<<< HEAD
	cout << json<>()._hello << endl;
=======

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
>>>>>>> 0ae3a95f95631a2eb135ebddb06991b9138315fb
	return 0; 
}
