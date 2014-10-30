/*
om636
Copyright (c) 2013 by Mark Busenitz
www.github.com/mucbuc
    
objective:
    - state owner
    - subject policy host
    - notify policy of requested state changes
 
type: concrete
 
dependancies:
    - std::tuple
    - om636/core/traverse
 
TODO:
     I/O:
     -   default whitespace seperator:
     
         stringstream s;
         s << "A B C";
         
         tuple< a, b, c > t;
         s >> t;
     
     -   comma seperator:
 
         stringstream s;
         s << "A, B, C,";
         
         tuple< a, b, c > t;
         s >> t.sep( ',' );
         
         cout << t.sep( ',' );   // ==> A, B, C
 
 note:
 - subject's that write to file could cause an exception in which the value probably shouldn't change
*/

#ifndef CONTEXT_H__INCLUDE_GUARD__45435435
#define CONTEXT_H__INCLUDE_GUARD__45435435

#include <tuple>
#include <type_traits>
#include <iostream>

#include <lib/traverse/interface.h>

namespace om636
{
    namespace default_subject
    {
        template<class> struct policy;
    }
    
    template<class T, template<class> class U = default_subject::policy>
    class context
    : public U< context< T, U > >
    {
        template<class, template<class> class> friend class context;
        
    public:
        
        // types
        typedef U< context< T, U > > subject_policy;
        typedef typename subject_policy::value_type value_type;
        
        // resources
        context();
        context(const context &);
        
        template<class W> context( const W & );
        template<class W, class X> context( const W &, const X & );
        virtual ~context() = default;
        context & operator=(context);
        template<class W> context & operator=(W);
        void swap(context &);
        
        // access
        typename std::add_lvalue_reference< value_type >::type value_ref();
        typename std::add_lvalue_reference< typename std::add_const< value_type >::type >::type value_ref() const;
 
        subject_policy & subject_ref();
        const subject_policy & subject_ref() const;
    
        template<class I>
        typename I::template traits<context>::result_type operator[](I);

        template<class I>
        typename I::template traits<const context>::result_type operator[](I) const;

        // conversion
        template<class W> W to_value() const;
        template<class W, class X> static W to_value(const X &);
        template<class W, class X, template<class> class Y> static W to_value(const context< X, Y > &);
        template<class W> static W to_value(const context &);
        
        template<class W, class X, template<class> class Y>
        static W converter(const context< X, Y > &);
        
        template<class W, class X> static W converter(const X &);
        
        // arithmetic
        template<class W> context operator+(const W &) const;
        context operator+(const context &) const;
        template<class W> context operator-(const W &) const;
        context operator-(const context &) const;
        template<class W> context operator*(const W &) const;
        context operator*(const context &) const;
        template<class W> context operator/(const W &) const;
        context operator/(const context &) const;
        template<class W> context operator%(const W &) const;
        context operator%(const context &) const;
        context operator-() const;
        
        template<class W> context & operator+=(const W &);
        context & operator+=(const context &);
        template<class W> context & operator-=(const W &);
        context & operator-=(const context &);
        template<class W> context & operator*=(const W &);
        context & operator*=(const context &);
        template<class W> context & operator/=(const W &);
        context & operator/=(const context &);
        template<class W> context & operator%=(const W &);
        context & operator%=(const context &);
        
        context operator++(int);
        context & operator++();
        context operator--(int);
        context & operator--();
        
        // comparisons
        bool operator==(const context &) const;
        bool operator!=(const context &) const;
        bool operator>=(context) const;
        bool operator>(context) const;
        bool operator<=(context) const;
        bool operator<(context) const;

    private:
        
        value_type m_internal_context_state;
    };
    
// non members
    template<class T, template<class> class U>
    void swap(context<T, U> &, context<T, U> &);
    
    template<class T, template<class> class U>
    int sign(const context<T, U> &);
    
    template<class T, class U, template<class> class V>
    T & operator<<(T & s, const context<U, V> &);
    
    template<class T, class U, template<class> class V>
    T & operator>>(T & s, context<U, V> &);

    namespace default_subject
    {
        template<class T>
        struct traits
        {
            typedef typename T::value_type value_type;
        };
        
        template<class T, template<class> class U>
        struct traits< context< T, U > >
        {
            typedef T value_type;
        };

        template<class T>
        struct policy
        {
            typedef T context_type;
            typedef typename traits<context_type>::value_type value_type;
            
            void on_swap( const context_type &, const context_type & );
            
            template<class V>
            static value_type on_init( V & );
            
            template<class V, class W>
            static value_type on_init( V &, const W & );
            
            template<class V>
            static V to_value( const context_type & );
            
            template<class U>
            static U & on_write( U &, const context_type & );
            
            template<class U>
            static U & on_read( U &, context_type & );
        };
    
        namespace Private
        {
            template<class>
            struct stream_in;
            
            template<class>
            struct stream_out;
        };
    }

}    // om636

#include "interface.hxx"

#endif // __CONTEXT_H__INCLUDE_GUARD__45435435