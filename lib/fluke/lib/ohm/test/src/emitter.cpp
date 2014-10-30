#include "test.h"

#include "emitter_fwd.h"
#include "emitter.h"

template< template<class, class> class T>
void test_emitter()
{
    check_dispatch_logic< T >();
    check_agent_life_time< T >();
    check_modify_while_traversal< T >();
    check_emit_while_emit< T >();
    check_emit_with_args< T >();
    check_emit_once< T >();
    check_on< T >();
    check_on_while_emit< T >();
    check_once_while_emit< T >();
    check_once_while_emit_recursive< T >();
}

int main()
{
    using namespace std;
    
    test_emitter< om636::control::Emitter >();
    cout << "om636::control::Emitter passed" << endl << endl;
    
    test_emitter< om636::control::Quemitter >();
    cout << "om636::control::Quemitter passed" << endl << endl;
    return 0;
}
