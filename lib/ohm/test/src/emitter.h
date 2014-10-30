#include "test.h"

#include <iostream>
#include <vector>
#include <src/emitter.h>
#include <src/quemitter.h>

#define FOOTER cout << __FUNCTION__ << " passed" << endl

using namespace std;
using namespace om636;

template< template<class, class> class T>
void check_emit_once()
{
    typedef T< string, function<void(int)> > emitter_type; 
    emitter_type e;
    
    unsigned counter( 0 ); 

    auto l( e.once( "hello", [&](int){
        ++counter;
    } ) ); 

    auto k( e.once( "allo", [&](int){
        ++counter;
    } ) ); 

    e.emit( "hello", 0 );
    e.emit( "hello", 0 );
    e.emit( "allo", 9 );
    e.emit( "allo", 9 );

    ASSERT( counter == 2 );

    FOOTER;
}

template< template<class, class> class T>
void check_emit_with_args()
{
    typedef T< string, function<void(int)> > emitter_type;
    typedef typename emitter_type::listener_type listener_type;
    emitter_type e;
    
    bool test_passed(0);
    string event("e");
    
    listener_type p( e.once( event, [&](int i){
        ASSERT( i == 99 );
        test_passed = 1;
    } ) );
    
    e.emit( event, 99 ); 
    
    ASSERT( test_passed );

    FOOTER;
}

template< template<class, class> class T>
void check_emit_while_emit()
{
    typedef T< string, function<void()>  > emitter_type;
    typedef typename emitter_type::listener_type listener_type;

    size_t counter(0);
    
    emitter_type e;
    string event("e");
    listener_type p( e.once( event, [&](){
        ++counter;
        e.emit( event );
    } ) );
    
    e.emit( event );

    ASSERT( counter == 1 );

    FOOTER;
}

/////////////////////////////////////////////////////////////////
template< template<class, class> class T>
void check_modify_while_traversal()
{
    typedef T< string, function<void()>  > emitter_type;
    typedef typename emitter_type::listener_type listener_type;
    
    static emitter_type emitter;
    static unsigned trap( 0 );
    static const string event( "load" );
    struct tester
    {
        static void trigger_trap()
        {
            ++trap;
        }
        
        static void remove()
        {
            ++trap;
            emitter.removeListeners( event );
        }
        
        static void removeAll()
        {
            ++trap;
            emitter.removeAllListeners();
        }
    };
    
    vector< listener_type > listeners;

    // test remove while traverse
    listeners.push_back( emitter.on( event, tester::remove ) );
    listeners.push_back( emitter.on( event, tester::remove ) );
    listeners.push_back( emitter.once( event, tester::remove ) );
    emitter.emit( event );
    ASSERT( trap == 1 );
    
    // test removeAll while traverse
    listeners.push_back( emitter.on( event, tester::removeAll ) );
    listeners.push_back( emitter.on( event, tester::removeAll ) );
    listeners.push_back( emitter.once( event, tester::removeAll ) );
    emitter.emit( event );
    ASSERT( trap == 2 );
    
    // test insert while traverse
    listeners.push_back( emitter.once( event, [&](){
        listeners.push_back( emitter.on( event, tester::trigger_trap ) );
        listeners.push_back( emitter.once( event, tester::trigger_trap ) );
    }));
    emitter.emit( event );
    ASSERT( trap == 2 );
    
    emitter.emit( event );
    ASSERT( trap == 4 );

    emitter.emit( event );
    ASSERT( trap == 5 );
    
    FOOTER;
}

/////////////////////////////////////////////////////////////////
template< template<class, class> class T>
void check_dispatch_logic()
{
    typedef T< string, function<void()> > emitter_type;
    typedef typename emitter_type::listener_type listener_type;

    static unsigned trap( 0 );
    struct tester
    {
        static void trigger_trap()
        {
            ++trap;
        }
    };
    
    emitter_type emitter;
    vector< listener_type > listeners;
    string event( "calculate answer to L.U. and E." );
    
    trap = 0;
    
    // check dead agent
    emitter.once( event, tester::trigger_trap );
    emitter.emit( event );
    ASSERT( trap == 0 );
    
    // check once
    listeners.push_back( emitter.once( event, tester::trigger_trap ) );
    emitter.emit( event );
    ASSERT( trap == 1 );
    emitter.emit( event );
    ASSERT( trap == 1 );
    
    // check on
    listeners.push_back( emitter.on( event, tester::trigger_trap ) );
    emitter.emit( event );
    ASSERT( trap == 2 );
    emitter.emit( event );
    ASSERT( trap == 3 );
    
    // check duplicate
    listeners.push_back( emitter.on( event, tester::trigger_trap ) );
    emitter.emit( event );
    ASSERT( trap == 5 );
    
    FOOTER;
}

/////////////////////////////////////////////////////////////////
template< template<class, class> class T> 
void check_agent_life_time()
{
    struct dummy_callback
    {
        dummy_callback()
        {
            ++instance_counter();
        }
        
        dummy_callback(const dummy_callback &)
        : dummy_callback()
        {}
        
        ~dummy_callback()
        {
            --instance_counter();
        }
        
        dummy_callback & operator=(const dummy_callback &) = default;
        
        static size_t & instance_counter()
        {
            static size_t counter( 0 );
            return counter;
        }
    };
    
    typedef T< string, dummy_callback > emitter_type;
    typedef typename emitter_type::listener_type listener_type;

    static string event( "init" );
    emitter_type emitter;
    
    if (1)
    {
        auto listener( emitter.on( event, dummy_callback() ) );
        emitter.removeListeners( event );
        
        // this reference is owned by the listener
        ASSERT( dummy_callback::instance_counter() == 1 );
    }
    ASSERT( !dummy_callback::instance_counter() );
    
    if (1)
    {
        auto listener( emitter.on( event, dummy_callback() ) );
        emitter.removeAllListeners();
        
        // this reference is owned by the listener
        ASSERT( dummy_callback::instance_counter() == 1 );
    }
    ASSERT( !dummy_callback::instance_counter() );

    if (1)
    {
        listener_type listener;
        if(1)
        {
            auto temp( emitter.on( event, dummy_callback() ) );
            ASSERT( dummy_callback::instance_counter() == 1 );
        
            listener = temp;
            
            ASSERT( dummy_callback::instance_counter() == 1 );
        }
        
        // this reference is owned by the emitter
        ASSERT( dummy_callback::instance_counter() == 1 );
    }
    
    emitter.removeListeners( event );
    ASSERT( !dummy_callback::instance_counter() );
    
    FOOTER;
}

template< template<class, class> class T>
void check_on()
{
    typedef T< string, function<void()> > emitter_type;
    typedef typename emitter_type::listener_type listener_type;

    emitter_type emitter;
    vector< listener_type > listeners;

    unsigned counter( 0 );
    
    listeners.push_back( emitter.on( "on", [&](){
        ++counter;
    } ) );

    emitter.emit( "on" );
    emitter.emit( "on" );
    emitter.emit( "on" );
    emitter.emit( "on" );
    
    ASSERT( counter == 4 );
    
    FOOTER;
}

template< template<class, class> class T>
void check_on_while_emit()
{
    typedef T< string, function<void()>  > emitter_type;
    typedef typename emitter_type::listener_type listener_type;

    emitter_type emitter;
    vector< listener_type > listeners;
    
    unsigned counter( 0 );
    
    listeners.push_back( emitter.once( "load", [&](){
        listeners.push_back( emitter.on( "on", [&](){
            ++counter;
        } ) );
        
        emitter.emit( "on" );
    } ) );
    
    emitter.emit( "load" );
    emitter.emit( "on" );
    
    ASSERT( counter == 2 );
    
    FOOTER;
}

template< template<class, class> class T>
void check_once_while_emit()
{
    typedef T< string, function<void()>  > emitter_type;
    typedef typename emitter_type::listener_type listener_type;

    emitter_type emitter;
    vector< listener_type > listeners;
    
    unsigned counter( 0 );
    
    listeners.push_back( emitter.once( "load", [&](){
        listeners.push_back( emitter.once( "on", [&](){
            ++counter;
        } ) );
        
        emitter.emit( "on" );
    } ) );
    
    emitter.emit( "load" );
    emitter.emit( "on" );
    
    ASSERT( counter == 1 );
    
    FOOTER;
}

template< template<class, class> class T>
void check_once_while_emit_recursive()
{    
    typedef T< string, function<void()>  > emitter_type;
    typedef typename emitter_type::listener_type listener_type;

    emitter_type emitter;
    vector< listener_type > listeners;
    
    unsigned counter( 0 );
    
    listeners.push_back( emitter.once( "on", [&](){
        ++counter;
        emitter.emit( "on" );
    }));
                        
    emitter.emit( "on" );
                        
    ASSERT( counter == 1 );

    FOOTER;
}
