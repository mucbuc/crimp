namespace om636
{
	namespace control
	{
		
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		Agent<T>::Agent( callback_type callback )
		: m_callback( callback )
		{}
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		void Agent<T>::invoke()
		{
			ASSERT( !is_dead() );
			m_callback();
		}
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        template<typename V>
        void Agent<T>::invoke( V v )
		{
			ASSERT( !is_dead() );
			m_callback( v );
		}
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		template<typename V, typename W>
        void Agent<T>::invoke( V v, W w)
		{
			ASSERT( !is_dead() );
			m_callback( v, w );
		}
		
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		void Agent<T>::kill_invoke()
		{
			ASSERT( !is_dead() );
			callback_type temp( m_callback ); 
			kill();
			temp();
		}
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        template<typename V>
        void Agent<T>::kill_invoke( V v )
		{
			ASSERT( !is_dead() );
			callback_type temp( m_callback );
			kill();
			temp( v );
		}
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		template<typename V, typename W>
        void Agent<T>::kill_invoke( V v, W w)
		{
			ASSERT( !is_dead() );
			callback_type temp( m_callback );
			kill();
			temp( v, w );
		
		}
		
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		void Agent<T>::kill()
		{
			m_callback = callback_type();
		}
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
		bool Agent<T>::is_dead()
		{
			return !m_callback;
		}

	}	//control
}	// om636
