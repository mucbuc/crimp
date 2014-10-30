/* 
    objective:
        thread safe read and append only data structure
    notes:  
        - values aren't traversed in any particular order
        - values appended while traversal may or may not get visited
    
    dev ideas:
        could have fixed size blocks (common sizes or primes)  
*/
 
#ifndef PSET_H__DgtvNfi7AQK9OCEXTxWJrlqLS0k2pz
#define PSET_H__DgtvNfi7AQK9OCEXTxWJrlqLS0k2pz


#include <algorithm> 
#include <fstream>
#include <mutex> 
#include <vector>
#include <memory> 

namespace om636
{
    template<typename T>
    struct default_pset_policy
    {
        static void on_head_pass( const T & ) {}
    };
    
	template<class T, template<class> class U = default_pset_policy>
	class pset 
	: public U< pset< T, U > > 
	{
        // feedback policy
        typedef U< pset< T, U > > fbp;
        
		typedef std::function< void(const T &) > visitor_type; 
		
	public: 
		typedef T value_type; 
		
		pset() = default; 
		~pset() = default;
		pset( const pset & ) = delete; 
		pset & operator=( const pset & ) = delete; 
		
		void append( const value_type & ); 
		
		template<class I> 
		void append( I, I ); 
		
		void traverse( visitor_type, std::function< void() > ) const;
        void traverse( visitor_type ) const; 

	private:
		
		struct node
		{
            virtual ~node() {}
            // not sure if this can be defaulted (works in xcode, doesn't work with g++)
            // online opinions seem mixed 
            
			virtual std::unique_ptr< node > & next() = 0;
			virtual void traverse( visitor_type ) = 0;
		};
	
        typedef std::unique_ptr< node > node_pointer; 
        
		struct node_base : node
		{
			node_base() : m_next() {}
            virtual ~node_base() {}
            
            node_pointer & next()
			{ 	return m_next; }
			
			virtual void traverse( visitor_type v )
			{
                if (m_next)
                    m_next->traverse( v );
            }
			
		private:
            
			node_pointer m_next; 
		}; 
		
		struct single_node : node_base 
		{
			single_node( const value_type & v )
			: node_base()
            , m_value( v )
			{}
		
            virtual ~single_node() {}
            
			virtual void traverse( visitor_type v )
			{ 
				v( m_value ); 
				node_base::traverse( v );
			}
				
		private: 	
			const value_type m_value; 
		}; 

		struct block_node : node_base 
		{
			template<class I> 
			block_node(I i, I e) 
			: node_base()
            , m_values( i, e )
			{}
			
            virtual ~block_node() {}
            
			virtual void traverse( visitor_type v )
			{ 
                std::for_each( m_values.begin(), m_values.end(), v ); 
				node_base::traverse( v );
			}
				
		private: 	
	
			const std::vector< value_type > m_values;
		}; 

        typedef std::mutex mutex_type; 

        void append( node * );
        
        node_pointer m_head;
        mutex_type m_mutex; 
	}; 

    // non members
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class S, class T, template<class> class U>
    S & operator>>( S &, pset< T, U > & );
    
	/////////////////////////////////////////////////////////////////////////////////////////////
    template<class S, class T, template<class> class U>
    S & operator<<(S &, const pset< T, U > & );
}

#include "pset.hxx"
#endif // PSET_H__DgtvNfi7AQK9OCEXTxWJrlqLS0k2pz