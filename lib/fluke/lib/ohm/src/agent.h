#ifndef AGENT_H__0OiXEmL5tPcgUywQFDMW6Gv1J8Hdzo
#define AGENT_H__0OiXEmL5tPcgUywQFDMW6Gv1J8Hdzo

namespace om636
{
	namespace control 
	{

		template< typename T > 
		struct Agent
		{
			typedef T callback_type;
			Agent( callback_type );
            
			void invoke();
           
            template<class V>
			void invoke(V);
            
            template<typename V, typename W>
            void invoke(V, W); 

			void kill_invoke();
           
            template<class V>
			void kill_invoke(V);
            
            template<typename V, typename W>
            void kill_invoke(V, W);
            
			void kill();
			bool is_dead();

		private: 
			callback_type m_callback;
		};

	}	//control
}	// om636

#include "agent.hxx"
#endif // AGENT_H__0OiXEmL5tPcgUywQFDMW6Gv1J8Hdzo