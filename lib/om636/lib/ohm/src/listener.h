#ifndef LISTENER_H__UCaPZDc8YNktrFzRqufGj4OJng9bym
#define LISTENER_H__UCaPZDc8YNktrFzRqufGj4OJng9bym


namespace om636
{
	namespace control 
	{

		template< typename T > 
		struct Listener
		{
			typedef T agent_type;
			Listener( agent_type );
			~Listener();
			Listener( const Listener & ) = default;
            Listener & operator=(const Listener &) = default;
            Listener() = default;
     	    
		private:
	        
			agent_type m_agent;
		};

	}	//control
}	// om636

#include "listener.hxx"
#endif // LISTENER_H__UCaPZDc8YNktrFzRqufGj4OJng9bym