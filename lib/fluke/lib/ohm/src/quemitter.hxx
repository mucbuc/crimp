namespace om636
{
    namespace control 
    {
        /////////////////////////////////////////////////////////////////////////////////////
        template<typename T, typename U>
        void Quemitter<T, U>::emit( event_type e)
        {
            function_type p( [e, this]() {
                base_type::emit( e );
            } ); 

            push_event( p );
        }
       
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T, typename U>
        template<class V> 
        void Quemitter<T, U>::emit( event_type e, V v )
        {
            function_type p( [e, v, this]() {
                base_type::emit( e, v );
            } ); 

            push_event( p );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<typename T, typename U>
        template<typename V, typename W> 
        void Quemitter<T, U>::emit( event_type e, V v, W w )
        {
            function_type p( [e, v, w, this]() {
                base_type::emit( e, v, w );
            } ); 

            push_event( p );
        }

        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        void Quemitter<T, U>::push_event( function_type f )
        {
            std::unique_lock<mutex_type> lock( m_mutex, std::try_to_lock );
            if (lock.owns_lock())
                do
                    f();
                while (m_queue.try_pop(f));
            else
                m_queue.push( f );
        }

    }   //control
}   // om636
