/* 
    Reference: http://www.drdobbs.com/article/print?articleId=184403745
*/

#ifndef ASSERT_H_9879879hkjh
#define ASSERT_H_9879879hkjh

#include <iostream>
#include <stdexcept>
#include <cstring>

#define NDEBUG 1

#ifndef NDEBUG

    #define ASSERT(expression) if (true) {}

    #define SMART_ASSERT( expr ) \
        if (false); \
        else    \
            struct local_t  \
            {   \
                local_t( const asserter_t & ) {} \
            } local_obj = asserter_t::make_asserter(false)

        // asserter_t
        class asserter_t
        {
        public:
            static const asserter_t make_asserter(bool) { return asserter_t(); }
            static const asserter_t make_asserter(bool, const char *) { return asserter_t(); }
            template<class T> const asserter_t operator()(const T &) const { return asserter_t(); } 
        };

#else

    #ifndef NTEST
        #define ASSERT_PASSED( expr ) \
        ;
    #else
        #define ASSERT_PASSED( expr ) std::cout << #expr << std::endl;
    #endif


    #define SMART_ASSERT_A(x) SMART_ASSERT_OP(x, B)
    #define SMART_ASSERT_B(x) SMART_ASSERT_OP(x, A)
    #define SMART_ASSERT_OP(x, next) SMART_ASSERT_A.print_current_val((x), #x).SMART_ASSERT_ ## next

    #define ASSERT( expr ) \
        if ( (expr) ) \
            ASSERT_PASSED( expr ) \
        else    \
            struct local_t  \
            {   \
                local_t( const asserter_t & o ) \
                {   \
                    if( !o.can_handle() )   \
                        memset( 0, 0, 1 );  \
                }   \
            } \
            local_obj = \
            asserter_t::make_asserter( expr ).print_error_message( __FILE__, __LINE__, __FUNCTION__, #expr ).SMART_ASSERT_A

    class asserter_message_out;
    template<class> class asserter_throw_t;
    
    // asserter_t
    class asserter_t 
    {	
    public:	
        virtual bool can_handle() const; 
        virtual const asserter_t & print_error_message(const char * file, int line, const char * function, const char * = "" ) const;  
        
        template<class U> const asserter_t & print_current_val(const U &, const char*) const; 
       
        static const asserter_t make_asserter(bool); 
        static const asserter_message_out make_asserter(bool, const char *); 
        template<class T> static const asserter_throw_t<T> make_asserter(bool, const char *); 
        
        asserter_t & SMART_ASSERT_A; 
        asserter_t & SMART_ASSERT_B; 
        
    protected:
        asserter_t(bool); 
        
    private:
        const bool m_value;
    };

    // asserter_message_out
    class asserter_message_out : public asserter_t 
    {
    public:
        asserter_message_out(bool, const char *); 
    
        virtual const asserter_t & print_error_message(const char * file, int line, const char * function, const char * = "" ) const;
    
    private:
        const char * m_message; 
    };

    // asserter_throw_t
    template<class T>
    class asserter_throw_t : public asserter_t 
    {
    public:
        asserter_throw_t(bool, const char *); 
        virtual bool can_handle(const char * file, int line, const char * function) const; 
        
    private: 
        const char * m_message; 
    };

#endif // NDEBUG

#include "assert.hxx"

#endif // ASSERT_H_9879879hkjh