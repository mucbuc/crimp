#include <iostream>

#include <src/data/content.json.h>

int main(int argc, const char * argv[])
{
	using namespace std;
	
	cout << static_port_data_content::json<>()._hello << endl;
	return 0; 
}
