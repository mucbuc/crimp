/* 
    objective: generic "growing object" implementation as found in "Advanced C++ Metaprogramming". 
    sample usage: expression templates, string compositions, 
 
*/ 


#ifndef _CHAIN_H_98787897700
#define _CHAIN_H_98787897700

#include <core/corefwd.h>  
#include <core/typetree.h>

namespace om636
{
    // chain<T, U> 
    template <class T, class U> 
    class chain
    {
        template<class, class> friend class chain; 
        
        // types
        typedef T traits_type; 
        typedef U type_list; 
        typedef typename traits_type::target_type target_type; 
        typedef typename type_list::left_type local_type; 
        typedef chain< traits_type, typename type_list::right_type > right_type; 
        typename traits_type::template storage_traits<local_type>::result_type m_obj; 
        typename traits_type::reference_type m_info; 
        
        void dump (target_type & x) const; 
        chain (const local_type & , const right_type &);
        
    public:
        
        template<class V> 
        chain< traits_type, type_tree<V, type_list> > 
        operator+ (const V &) const; 
        
        const chain & operator>> (target_type &) const; 
        operator target_type() const; 
        
    private: 
        
        const right_type & m_right; 
        
        // undefined
        chain (const chain &); 
        chain & operator= (const chain &); 
    }; 
    
    // chain<T, null_type>
    template <class T> 
    class chain< T, null_type > 
    {
        template<class, class> friend class chain; 
        
        // types
        typedef T traits_type; 
        typedef typename traits_type::information_type information_type; 
        typedef typename traits_type::target_type target_type; 
        
        information_type m_info; 
        void dump(target_type &) const; 
    public:
        
        explicit chain (const information_type & i = information_type()); 
        
        template<class U> 
        chain< traits_type, type_tree< U, null_type > > operator+(const U &) const;            
        
        const chain & operator>> (target_type &) const; 
        
        operator target_type() const; 
       
    private: 
        
        // undefined
        chain (const chain &); 
        chain & operator= (const chain &); 
    };
    
}   // om636

#include <core/chain.hxx>

#endif // _CHAIN_H_98787897700