#include "test.h"
#include "context_test.h"
#include "observer_test.h"

#include <tuple>

int main(int argc, const char * argv[])
{
    using namespace std;
    using namespace om636;

    run_context_test();
	
	run_observer_test<void>();
	
	return 0;
}
