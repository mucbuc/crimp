#include <iostream>

#include <tmp/src/data/content.json.h>

int main()
{
	using namespace std;
	
	cout << static_port_data_content::json<>()._hello << endl;
	return 0; 
}
