namespace om636
{
	namespace control
	{
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        Listener<T>::Listener( agent_type agent )
		: m_agent( agent )
		{}
        
		/////////////////////////////////////////////////////////////////////////////////////
		template<typename T>
        Listener<T>::~Listener()
		{
            // this is the only listener, the other owner is the batch
            if (m_agent.use_count() == 2)
                m_agent->kill();
        }
	}	//control
}	// om636
