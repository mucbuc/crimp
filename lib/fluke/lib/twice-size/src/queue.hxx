namespace om636
{
    /////////////////////////////////////////////////////////////////////////////////////////////
    // queue<T>
    /////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, template<typename> class U>
	queue<T, U>::queue()
	: m_mutex()
	, m_queue()
	, m_condition()
	{}
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, template<typename> class U>
	queue<T, U>::queue( const queue & rhs )
	: m_mutex()
	, m_queue( rhs.m_queue )
	, m_condition()
    {}
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, template<typename> class U>
	queue<T, U> & queue<T, U>::operator=(queue rhs)
	{
		swap( rhs ); 
		return * this;
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, template<typename> class U>
	void queue<T, U>::swap( queue & rhs)
	{
        typedef std::unique_lock< mutex_type > lock_type;
        
        lock_type left_lock( m_mutex, std::defer_lock );
        lock_type right_lock( m_mutex, std::defer_lock );
        std::lock( left_lock, right_lock );
        
        fbp::on_swap_locked( * this, rhs );

        std::swap( m_queue, rhs.m_queue );
	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, template<typename> class U>
	void queue<T, U>::push(T v)
	{
        lock_type lock( m_mutex );
        
        fbp::on_push_locked( * this );
        
        m_queue.push(v);
        m_condition.notify_one();
    }
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, template<typename> class U>
	void queue<T, U>::wait_and_pop(T & v)
	{
        std::unique_lock< std::mutex > lock( m_mutex );
        m_condition.wait( lock, [this]{ return ! m_queue.empty(); } );
        v = m_queue.front();
        m_queue.pop();
    }
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, template<typename> class U>
	std::shared_ptr<T> queue<T, U>::wait_and_pop()
	{
	    std::unique_lock< std::mutex > lock( m_mutex );
        m_condition.wait( lock, [this]{ return ! m_queue.empty(); } );
        auto result( std::make_shared<T>( m_queue.front() ) );
        m_queue.pop();
        return result;
    }
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, template<typename> class U>
	bool queue<T, U>::try_pop(T & value)
	{
        lock_type lock( m_mutex );
        if (m_queue.empty())
            return 0;
        value = m_queue.front();
        m_queue.pop();
        return 1;
 	}
	
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, template<typename> class U>
	std::shared_ptr<T> queue<T, U>::try_pop()
	{
        lock_type lock( m_mutex );
        if (m_queue.empty())
            return std::shared_ptr<T>();
        auto result( std::make_shared<T>( m_queue.front() ) );
        m_queue.pop();
        return result;
    }
    
	/////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, template<typename> class U>
	bool queue<T, U>::empty() const
	{
        lock_type lock( m_mutex );
        return m_queue.empty(); 
	}

	/////////////////////////////////////////////////////////////////////////////////////////////
	template<typename T, template<typename> class U> 
	void swap( queue<T> & lhs, queue<T> & rhs)
	{
		lhs.swap( rhs ); 
	}		
}
