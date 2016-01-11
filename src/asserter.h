/* 
    Reference: http://www.drdobbs.com/article/print?articleId=184403745
*/

#ifndef ASSERT_H_9879879hkjh
#define ASSERT_H_9879879hkjh

#include <cstring>
#include <iostream>

#ifdef NDEBUG

     #define ASSERT( expr ) \
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

    #define SMART_ASSERT_A(x) SMART_ASSERT_OP(x, B)
    #define SMART_ASSERT_B(x) SMART_ASSERT_OP(x, A)
    #define SMART_ASSERT_OP(x, next) SMART_ASSERT_A.print_current_val((x), #x).SMART_ASSERT_ ## next

    #ifndef TARGET_TEST
        #define TARGET_TEST 0 
    #endif

    #define ASSERT( expr ) \
        if (!TARGET_TEST && (expr)); \
        else    \
            struct local_t  \
            {   \
                local_t( const asserter_t & o ) \
                {   \
                    if( !o.can_handle() )   \
                        asserter_t::on_assert_fail();  \
                }   \
            } \
            local_obj = \
            asserter_t::make_asserter( expr ) \
            .print_message( __FILE__, __LINE__, __FUNCTION__, #expr ) \
            .archive_result( __FILE__, __LINE__, __FUNCTION__, #expr ) \
            .SMART_ASSERT_A

    // asserter_t
    class asserter_t final
    {	
    public:	

        bool can_handle() const; 
        
        const asserter_t & print_message(
            const char * file, 
            int line, 
            const char * function, 
            const char * = "" ) const;  

        const asserter_t & archive_result(
            const char * file, 
            int line, 
            const char * function, 
            const char * = "" ) const; 
        
        template<class U> const asserter_t & print_current_val(const U &, const char*) const; 
       
        static const asserter_t make_asserter(bool); 
        
        asserter_t & SMART_ASSERT_A; 
        asserter_t & SMART_ASSERT_B; 
        
        static void on_assert_fail();

    protected:
        asserter_t(bool); 
        
    private:
        const bool m_value;
    };

    #include "asserter.hxx"

#endif // NDEBUG

#endif // ASSERT_H_9879879hkjh