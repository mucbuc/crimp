#ifndef QUEUE_H__bkTdfGDgc2m7s1vEHICwQupRyzFrJP
#define QUEUE_H__bkTdfGDgc2m7s1vEHICwQupRyzFrJP

#include <queue>
#include <memory> 
#include <thread>
#include <mutex> 
#include <condition_variable>

namespace om636
{
    template<typename T>
    struct default_queue_policy
    {
        void on_push_locked( T & ) {}
        void on_swap_locked( T &, T & ) {}
    };
    
	template<typename T, template<typename> class U = default_queue_policy>
	class queue
    : public U< queue< T, U > > 
	{  
    public:
        
        typedef T value_type; 
        
		queue(); 
		queue(const queue &); 
		queue & operator=(queue); 
		void swap( queue & ); 
		
		void push(value_type); 
		void wait_and_pop(value_type &); 
		std::shared_ptr<value_type> wait_and_pop(); 
		bool try_pop(value_type &); 
		std::shared_ptr<value_type> try_pop(); 
		bool empty() const;
    
    private:
        
        // feedback policy
        typedef U< queue< T, U > > fbp;
        
        typedef std::mutex mutex_type; 
        typedef std::lock_guard< std::mutex > lock_type;
        
        mutable mutex_type m_mutex;
        std::queue<T> m_queue;
        std::condition_variable m_condition;
    };

	template<typename T, template<typename> class U>
	void swap( queue<T> &, queue<T> &); 
}

#include "queue.hxx"
#endif // __QUEUE_H__bkTdfGDgc2m7s1vEHICwQupRyzFrJP