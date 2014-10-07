#include "assert.h"

#undef SMART_ASSERT_A 
#undef SMART_ASSERT_B
#undef SMART_ASSERT_OP
#undef SMART_ASSERT

#ifdef NDEBUG

/////////////////////////////////////////////////////////////////////////////////////////////
// assereter_t
/////////////////////////////////////////////////////////////////////////////////////////////
asserter_t::asserter_t(bool value) 
	: SMART_ASSERT_A( * this )
    , SMART_ASSERT_B( * this )
    , m_value( value )
{}

/////////////////////////////////////////////////////////////////////////////////////////////
bool asserter_t::can_handle() const
{	
    using namespace std;
    return m_value; 	
}

/////////////////////////////////////////////////////////////////////////////////////////////
const asserter_t & asserter_t::print_error_message(const char * file, int line, const char * function, const char * message) const
{
    using namespace std;
    cout << "assertion failed: " << message << 
    endl << "file: " << file << 
    endl << "line: " << line << 
    endl << "function: " << function << endl;
    return * this;
}

/////////////////////////////////////////////////////////////////////////////////////////////
const asserter_t asserter_t::make_asserter(bool value)
{	return asserter_t(value); 	}

/////////////////////////////////////////////////////////////////////////////////////////////
const asserter_message_out asserter_t::make_asserter(bool value, const char * message)
{	return asserter_message_out(value, message); 	}

/////////////////////////////////////////////////////////////////////////////////////////////
// asserter_message_out
/////////////////////////////////////////////////////////////////////////////////////////////
asserter_message_out::asserter_message_out(bool value, const char * message)
    : asserter_t(value)
    , m_message( message )
{}

/////////////////////////////////////////////////////////////////////////////////////////////
const asserter_t & asserter_message_out::print_error_message(const char * file, int line, const char * function, const char * ) const
{
    return asserter_t::print_error_message( file, line, function, m_message ); 
}

#endif 