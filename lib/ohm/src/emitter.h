#ifndef EMITTER_H__iFZqmDoIwhGaYO3df4xe5LCQXrbBvj
#define EMITTER_H__iFZqmDoIwhGaYO3df4xe5LCQXrbBvj

#include <map>
#include <memory>
#include <set>

#include "agent.h"
#include "listener.h"

namespace om636
{
	namespace control 
	{
		template<typename T, typename U> 
		class Emitter 
		{
		public: 

		    typedef T event_type;
			typedef U callback_type;
			typedef Agent< callback_type > agent_type;
            typedef std::shared_ptr< agent_type > pointer_type;
            typedef Listener< pointer_type > listener_type;

			Emitter() = default;
			virtual ~Emitter() = default;
            Emitter(const Emitter &) = delete;
            Emitter & operator=(const Emitter &) = delete;
			
			listener_type on( event_type, callback_type );
			listener_type once( event_type, callback_type );
			
			void removeListeners( event_type );
			void removeAllListeners();

			void emit( event_type );
			
			template<class V> 
			void emit( event_type, V );
			
			template<typename V, typename W> 
			void emit( event_type, V, W );
            
		private:

            typedef std::multiset< pointer_type > batch_type;
			typedef std::map< event_type, batch_type > map_type;
			
            static void process_and_kill( const batch_type & );
            
            template<typename V>
            static void process_and_kill( const batch_type &, V );
            
            template<typename V, typename W>
            static void process_and_kill( const batch_type &, V, W );
            
            static void process( const batch_type & );
            
            template<typename V>
            static void process( const batch_type &, V );
            
            template<typename V, typename W>
            static void process( const batch_type &, V, W );
            
            batch_type copy_batches(event_type);
            void merge_batches();
            
            static void merge_maps(map_type &, map_type &);
            static void kill_all(batch_type &);
            static void kill_all(map_type &);
            
			map_type m_repeat;
            map_type m_repeat_add;
			map_type m_once;
			map_type m_once_add;
		};
	}	//control
}	// om636

#include "emitter.hxx"

#endif 