#include <src/queue.h>
#include <src/pset.h>
#include <src/stack.h>

#include <memory>
#include <cmath>
#include <thread>
#include <iostream>
#include <sstream>

#include "test.h"

namespace om636
{
    template<typename T>
    struct wait_loop
    {
        std::condition_variable m_done_condition;
        bool m_done;
        std::mutex m_mutex;
    
        wait_loop()
        : m_done( 0 )
        {}
        
        void finish()
        {
            m_done = 1; 
            m_done_condition.notify_one();
        }
        
        void wait()
        {
            std::unique_lock<std::mutex> lock( m_mutex );
            m_done_condition.wait( lock, [&] { return m_done; } );
        }
    };

    
    template<typename T>
    struct test_policy_stack
    {
        static void on_pop_locked( T & s )
        {
            using namespace std;

            std::thread a( [&]() {
                ASSERT( s.empty() );
                m_loop.finish();
            } );
            a.detach();
        }
        
        static void on_swap_locked( T & l, T & r )
        {
        }

   // private:
        
        static wait_loop<void> m_loop;
    };
    
    template<typename T>
    wait_loop<void> test_policy_stack<T>::m_loop;
    
    template<typename T>
    struct test_policy_queue
    {
        test_policy_queue() : m_first( 1 ) {}
        
        void on_push_locked( T & q )
        {
            if (m_first)
            {
                m_first = 0;
                std::thread a( [&]() {
                    q.push( 2 );
                    m_loop.finish(); 
                } );
                a.detach();
            }
        }
            
        void on_swap_locked( T & l, T & r)
        {
        }
        
        static wait_loop<void> m_loop;
        
    private:
        bool m_first;
        
    };

    template<typename T>
    wait_loop<void> test_policy_queue<T>::m_loop;
    
    template<typename T>
    void check_stack_locks()
    {
        using namespace std; 
		typedef om636::stack< int, test_policy_stack > stack_type;
		
        stack_type s, t;
		s.push( 1 );
        s.pop();
        t.push( 1 );
        stack_type::m_loop.wait();
        
        cout << "check_stack_locks passed" << endl;
    }
    
    template<typename T>
    void check_queue_locks()
    {
		using namespace std;
        typedef om636::queue< int, test_policy_queue > queue_type;

        queue_type q;
        q.push( 1 );
        
        shared_ptr< int > a( q.wait_and_pop() );
        shared_ptr< int > b( q.wait_and_pop() );
        
        queue_type::m_loop.wait();
        
        ASSERT( * a == 1 && * b == 2 );
    
        cout << "check_queue_locks passed" << endl;
    }
    
    template<class T>
    struct test_policy
    {
        static void on_head_pass( const T & r )
        {
            const_cast< T & >(r).append( 33 );
        }
    };
    
    struct pset_checker
    {
        pset_checker( bool & passed )
        : m_passed( passed )
        , m_first( 1 )
        {}
        
        template<class T>
        void operator()(const T & t)
        {
            if (m_first)
                m_passed = t == 33;
            m_first = 0;
        }
    
        bool & m_passed;
        bool m_first;
    };
    
    template<class T>
    void check_pset()
    {
        using namespace om636;
        using namespace std;
        
        pset< int, test_policy > r;
        
        r.append( 0 );
        r.append( 1 );
        
        vector< int > v;
        v.push_back( 3 );
        v.push_back( 4 );
        v.push_back( 5 );
        v.push_back( 6 );
        r.append( v.begin(), v.end() );

        bool passed( 0 ); 
        r.traverse( pset_checker( passed ) );
        
        ASSERT( passed );
    
        std::cout << "check pset passed" << std::endl;
    }

}   // om636