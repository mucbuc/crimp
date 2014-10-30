
namespace om636
{

    /////////////////////////////////////////////////////////////////////////////////////////////
    // stack<T>
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, template<typename> class U>
    stack<T, U>::stack()
    : m_stack()
    , m_mutex()
    {}

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, template<typename> class U>
    stack<T, U>::stack( const stack & rhs )
    {
        lock_type lock( m_mutex );
        m_stack = rhs.m_stack;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, template<typename> class U>
    stack<T, U> & stack<T, U>::operator=(stack rhs)
    {
        swap( rhs );
        return * this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, template<typename> class U>
    void stack<T, U>::swap(stack & rhs)
    {
        if (this == & rhs)
            return;
        
        typedef std::unique_lock< mutex_type > lock_type;
        
        lock_type left_lock( m_mutex, std::defer_lock );
        lock_type right_lock( rhs.m_mutex, std::defer_lock );
  
        std::lock( left_lock, right_lock );
        
        fbp::on_swap_locked( * this, rhs );
        
        m_stack.swap( rhs.m_stack );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, template<typename> class U>
    void stack<T, U>::push( value_type v )
    {
        lock_type lock( m_mutex );
        m_stack.push( v );
    }
        
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, template<typename> class U>
    std::shared_ptr< typename stack<T, U>::value_type > stack<T, U>::pop()
    {
        lock_type lock( m_mutex );

        fbp::on_pop_locked( * this );

        if (m_stack.empty())
            throw( empty_stack() );
        
        std::shared_ptr<T> const res( std::make_shared<T>( m_stack.top() ) );
        m_stack.pop();
        
        return res;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, template<typename> class U>
    void stack<T, U>::pop(T & value)
    {
        lock_type lock( m_mutex );
        
        if (m_stack.empty())
            throw( empty_stack() );
        
        fbp::on_pop_locked( * this );
        
        value = m_stack.top();
        m_stack.pop();
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, template<typename> class U>
    bool stack<T, U>::empty() const
    {
        lock_type lock( m_mutex );
        return m_stack.empty(); 
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<typename T, template<typename> class U>
    void swap( stack<T, U> & lhs, stack<T, U> & rhs)
    {
        lhs.swap( rhs );
    }
}