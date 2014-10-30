#ifndef _RANGE_H_8900700
#define _RANGE_H_8900700

#include <src/components/componentsfwd.h>
#include <src/core/core.h>
#include <tuple>

namespace om636
{
	template<int N>
	class index 
	{
		typedef int_to_type<N> index_type; 

	public:
	
		template<class U>	
		struct traits
		{	
			typedef typename std::tuple_element<N, typename U::list_type >::type value_type;
			typedef typename add_reference< value_type >::result_type result_type; 
		};
		
		template<class U>
		struct traits< const U > 
		{	
			typedef typename std::tuple_element<N, typename U::list_type>::type value_type;
			typedef typename add_reference< typename add_const< value_type >::result_type >::result_type result_type; 	
		};
	
		template<class U> typename traits<U>::result_type operator()(U & v)
		{	
		//	return v.at( index_type() ).value_ref(); 
			return std::get<N>( v.value_ref() );//.value_ref();
		}
			
		template<class U> typename traits<const U>::result_type operator()(const U & v)
		{	return std::get<N>( v.value_ref() ); }
    };

	template<class T, class U>
	struct sequence_ref
	{
		typedef T value_type;
		typedef U sequence_type; 
	
		sequence_ref( value_type & v) : m_value( v ) {} 
		
		// next this needs to provide composite functionality and map the values. 
	
		
	private:
		
		value_type & m_value;

		// undefined 
		sequence_ref( const sequence_ref & ); 
		sequence_ref & operator=(sequence_ref);
	};
	
	template<int B, int S, int E>  
	struct sequence
	{
		enum { begin = B, stride = S, end = E };
		
		template<class U>	
		struct traits
		{	typedef sequence_ref<U, sequence> result_type; 	};
		
		template<class U>
		struct traits< const U > 
		{	typedef sequence_ref<const U, sequence> result_type; 	};
				
		// 
		template<class U> typename traits<U>::result_type 
		operator()(U & v)
		{	
			return sequence_ref<U, sequence>( v ); 
		}
	
		template<class U> typename traits<const U>::result_type
		operator()(const U & v)
		{
			return sequence_ref<const U, sequence>( v ); 
		}
	};
	
}	// om636 

#endif // _RANGE_H_8900700