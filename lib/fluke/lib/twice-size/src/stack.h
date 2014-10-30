#ifndef STACK_H__lDbByacR7uf0imVroPHJedFqwh9M5p
#define STACK_H__lDbByacR7uf0imVroPHJedFqwh9M5p

#include <stack>
#include <memory>
#include <thread>
#include <mutex>

namespace om636
{
    template<typename T>
    struct default_stack_policy
    {
        static void on_pop_locked( T & ) {}
        static void on_swap_locked( T & ) {}
    };
    
    template<typename T, template<typename> class U = default_stack_policy >
	class stack
    : public U< stack< T, U > >
	{
		// feedback policy
        typedef U< stack< T, U > > fbp;
        
    public:
        
        struct empty_stack{};
        
        typedef T value_type;
		
		stack(); 
		stack( const stack & ); 
		stack & operator=(stack); 
		
		void push( value_type v ); 
		
		std::shared_ptr<value_type> pop(); 
		void pop(T &); 
		bool empty() const;
        
        void swap( stack & );
        
	private:
        typedef std::lock_guard< std::mutex > lock_type;
        typedef std::mutex mutex_type; 
        
		std::stack<T> m_stack;
		mutable mutex_type m_mutex;
	}; 

    template<typename T, template<typename> class U > 
    void swap( stack<T, U> &, stack<T, U> & );
}

#include "stack.hxx"

#endif // __STACK_H__lDbByacR7uf0imVroPHJedFqwh9M5p