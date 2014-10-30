namespace om636
{
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    // chain< T, null_type >
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T> 
    void chain< T, null_type >::dump(target_type &) const
    {}

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    chain< T, null_type >::chain (const information_type & i)
    : m_info( i )
    {} 

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    template<class U> 
    chain< typename chain< T, null_type >::traits_type, type_tree< U, null_type > > chain< T, null_type >::operator+(const U & x) const
    {
        return chain< traits_type, type_tree< U, null_type > >( x, * this ); 
    }            

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    const chain< T, null_type > & chain< T, null_type >::operator>> (target_type & x) const
    {
        x = target_type(); 
        return * this; 
    } 

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    chain< T, null_type >::operator target_type() const
    {
        return target_type(); 
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    // chain<T, U> 
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U> 
    void chain<T, U>::dump (target_type & x) const
    {
        // todo: add reverse sequece of dump and transimt determined at compile time 
        
        m_right.dump(x);
        traits_type::transmit( x, m_obj ); 
    } 

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U> 
    chain<T, U>::chain (const local_type & x, const right_type & left)
    : m_obj( x )
    , m_right( left )
    , m_info( left.m_info )
    {
        traits_type::update(x, m_info); 
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U> 
    template<class V> 
    chain< typename chain<T, U>::traits_type, type_tree< V, typename chain<T, U>::type_list > > 
    chain<T, U>::operator+ (const V & x) const
    {
        typedef chain< traits_type, type_tree< V, type_list > > result_type;
        return result_type (x, * this);
    } 

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U> 
    const chain<T, U> & chain<T, U>::operator>> (target_type & x) const
    {
        traits_type::dispatch(x, m_info); 
        dump(x);  
        return * this; 
    } 

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U> 
    chain<T, U>::operator target_type() const
    {
        target_type x; 
        * this >> x; 
        return x; 
    } 

}   // om636
