#ifndef _COREFWD_H_INCLUDE_GUARD_98798798
#define _COREFWD_H_INCLUDE_GUARD_98798798

namespace om636
{
	// core.h
	struct null_type;
	struct empty_type;
    template< class = empty_type> struct empty_template;
    template<class> struct type_to_type;
	template<int> struct int_to_type;
	
    // chain.h
    template <class T, class U = null_type>
    class chain;
    
	// typetraits.h
	template<class T> struct type_traits;
    
    template< class T, template<class> class U = empty_template >
    struct generate_scatter_hierarchy;
    
    template< class, template<class, class> class, class = empty_type >
    struct generate_linear_hierarchy;

	// typeutills.h
    template<class> struct is_builtin_type;
    template<bool, class, class> struct if_then_else;
	template<class> struct switch_const; 
	template<class>	struct add_reference; 
	template<class> struct add_const; 
	template<class> struct remove_pointer; 
    template<class> struct remove_reference; 
    
    template<class> struct ctor_traits;
    
}	// om636	

#endif // _COREFWD_H_INCLUDE_GUARD_98798798
