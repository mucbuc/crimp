namespace om636
{
#pragma mark - context
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    // context
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    context<T, U>::context()
    : subject_policy()
    , m_internal_context_state( subject_policy::on_init( subject_ref() ) )
    {}
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    template<class W>
    context<T, U>::context( const W & init )
    : subject_policy()
    , m_internal_context_state( subject_policy::on_init( subject_ref(), init ) )
    {}
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    template<class W, class X>
    context<T, U>::context( const W & init, const X & _subject )
    : subject_policy( _subject )
    , m_internal_context_state( subject_policy::on_init( subject_ref(), init ) )
    {}

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    context<T, U>::context(const context & _c)
    : subject_policy( _c.subject_ref() )
    , m_internal_context_state( _c.m_internal_context_state )
    {}
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    context<T, U> & context<T, U>::operator=(context _c)
    {
        swap( _c );
        return *this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    template<class W>
    context<T, U> & context<T, U>::operator=(W _c)
    {
        context temp( _c );
        swap( temp );
        return * this;
    }
    
     /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    template<class I>
    typename I::template traits< context<T, U> >::result_type context<T, U>::operator[](I i)
    {
        return i( * this );
    }
        
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    template<class I>
    typename I::template traits< const context<T, U> >::result_type context<T, U>::operator[](I i) const
    {
        return i( * this );
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    auto context<T, U>::value_ref() -> typename std::add_lvalue_reference< value_type >::type
    {
        return m_internal_context_state;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    auto context<T, U>::value_ref() const -> typename std::add_lvalue_reference< typename std::add_const< value_type >::type >::type
    {
        return m_internal_context_state;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    auto context<T, U>::subject_ref() -> subject_policy & 
    {
        return * this;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    auto context<T, U>::subject_ref() const -> const subject_policy &
    {
        return * this;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    void context<T, U>::swap(context & i)
    {     
        this->on_swap( * this, i );
    }

    /*    conversions    */
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    template<class W>
    W context<T, U>::to_value() const
    {
        return to_value<W>( * this );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    template<class W, class X>
    W context<T, U>::to_value(const X & n)
    {
        return n;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    template<class W>
    W context<T, U>::to_value(const context & n)
    {
        return subject_policy::template to_value<W>( n );
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    template<class W, class X, template<class> class Y>
    W context<T, U>::to_value(const context< X, Y > & n)
    {
        return context< X, Y >::subject_policy::template to_value<W>( n );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    template<class W, class X, template<class> class Y>
    W context<T, U>::converter(const context< X, Y> & v)
    {
        return v.template to_value<W>();
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    template<class W, class X>
    W context<T, U>::converter(const X & v)
    {
        return v;
    }
    
    /* arithmetic operators    */
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    template<class W>
    context<T, U> context<T, U>::operator+(const W & v) const
    {
        context result( * this );
        result.on_add( result, context(v) );
        return result;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    context<T, U> context<T, U>::operator+(const context & v) const
    {
        context result( * this );
        result.on_add( result, v );
        return result;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
        template<class W>
    context<T, U> & context<T, U>::operator+=(const W & v)
    {
            this->on_add( * this, context( v ) );
        return * this;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    context<T, U> & context<T, U>::operator+=(const context & v)
    {
        this->on_add( * this, v );
        return * this;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    template<class W>
    context<T, U> & context<T, U>::operator-=(const W & v)
    {
        this->on_subtract( * this, context(v) );
        return * this;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    context<T, U> & context<T, U>::operator-=(const context & v)
    {
        this->on_subtract( * this, v);
        return * this;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    template<class W>
    context<T, U> context<T, U>::operator-(const W & v) const
    {
        context result( * this );
        result.on_subtract( result, context( v ) );
        return result;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    context<T, U> context<T, U>::operator-(const context & v) const
    {
        context result( * this );
        result.on_subtract( result, v );
        return result;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    template<class W>
    context<T, U> context<T, U>::operator*(const W & v) const
    { 
        context result( * this );
        result.on_mult( result, context( v ) );
        return result;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    context<T, U> context<T, U>::operator*(const context & v) const
    {
        context result( * this );
        result.on_mult( result, v );
        return result;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    template<class W>
    context<T, U> & context<T, U>::operator*=(const W & v)
    {
        this->on_mult( * this, context(v) );
        return * this;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    context<T, U> & context<T, U>::operator*=(const context & v)
    {
        this->on_mult( * this, v );
        return * this;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    template<class W>
    context<T, U> context<T, U>::operator/(const W & v) const
    {
        context result( * this );
        result.on_divide( result, context(v) );
        return result;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    context<T, U> context<T, U>::operator/(const context & v) const
    {
        context result(*this);
        result.on_divide(result, v);
        return result;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    template<class W>
    context<T, U> & context<T, U>::operator/=(const W & v)
    {
        this->on_divide(*this, context(v) );
        return *this;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    context<T, U> & context<T, U>::operator/=(const context & v)
    {
        this->on_divide(*this, v);
        return *this;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    template<class W>
    context<T, U> context<T, U>::operator%(const W & v) const
    {
        context result( * this);
        result.on_remainder( result, context(v) );
        return result;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    context<T, U> context<T, U>::operator%(const context & v) const
    {
        context result( * this);
        result.on_remainder( result, v );
        return result;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    template<class W>
    context<T, U> & context<T, U>::operator%=(const W & v)
    {
        this->on_remainder( context(v) );
        return * this;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    context<T, U> & context<T, U>::operator%=(const context & v)
    {
        this->on_remainder( * this, v );
        return * this;
    }
    
    /*     unary operators     */
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    context<T, U> context<T, U>::operator-() const
    {
        context result( 0 );
        result -= * this;
        return result;
    }
    
    /*    comparisons    */
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    bool context<T, U>::operator==(const context & n) const
    {
        return this->on_equal( * this, n );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    bool context<T, U>::operator!=(const context & n) const
    {
        return !this->on_equal( * this, n );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    bool context<T, U>::operator>=(context n) const
    {
        return this->on_cmp( * this, n ) >= 0;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    bool context<T, U>::operator>(context n) const
    {
        return this->on_cmp( * this, n ) > 0;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    bool context<T, U>::operator<=(context n) const
    {
        return this->on_cmp( * this, n ) <= 0;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    bool context<T, U>::operator<(context n) const
    {
        return this->on_cmp( * this, n ) < 0;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    context<T, U> context<T, U>::operator++(int)
    {
        context result( * this );
        this->on_inc( * this );
        return result;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    context<T, U> & context<T, U>::operator++()
    {
        this->on_inc( * this );
        return * this;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    context<T, U> context<T, U>::operator--(int)
    {
        context result( * this );
        this->on_dec( * this );
        return result;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    context<T, U> & context<T, U>::operator--()
    {
        this->on_dec( * this );
        return * this;
    }

#pragma mark - non members
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    void swap(context<T, U> & lhs, context<T, U> & rhs)
    {
        lhs.swap( rhs );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, template<class> class U>
    int sign(const context<T, U> & c)
    {
        return c.on_sign( c );
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, template<class> class V>
    T & operator<<(T & s, const context<U, V> & c)
    {
        context<U, V>::on_write( s, c );
        return s;
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T, class U, template<class> class V>
    T & operator>>(T & s, context<U, V> & c)
    {
        context<U, V>::on_read( s, c );
        return s;
    }
    
    namespace default_subject
    {
        namespace Private
        {
            template<class T>
            struct stream_out
            {
                stream_out( const stream_out & ) = default;
                
                template<class U>
                U operator()(const U & u) const
                {
                    m_stream << u;
                    return u;
                }
                
                template<class U, class V>
                V operator()(const U & u, const V & v) const
                {
                    m_stream << " " << v;
                    return v;
                }
                
                T m_stream;
            };
        
            template<class T>
            struct stream_in
            {
                stream_in( const stream_in & ) = default;
                
                template<class U>
                U operator()(U & u) const
                {
                    m_stream >> u;
                    return u;
                }
                
                template<class U, class V>
                V operator()(U & u, V & v) const
                {
                    m_stream >> v;
                    return v;
                }
                
                T m_stream;
            };
        }
            
        /////////////////////////////////////////////////////////////////////////////////////////////
        // policy
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        template<class V>
        auto policy<T>::on_init( V & ) -> value_type
        {
            return value_type();
        }

        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        template<class V, class W>
        auto policy<T>::on_init( V &, const W & v ) -> value_type
        {
            return value_type(v);
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        template<class V>
        V policy<T>::to_value( const context_type & c )
        {
            return V( c.value_ref() );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        void policy<T>::on_swap( const context_type &, const context_type & )
        {}
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        template<class U>
        U & policy<T>::on_write( U & s, const context_type & c )
        {
            Private::stream_out<U &> op = { s };
            traverse::pairs( c.value_ref(), op );
            return s;
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        template<class U>
        U & policy<T>::on_read( U & s, context_type & c )
        {
            Private::stream_in<U &> op = { s };
            traverse::pairs( c.value_ref(), op );
            return s;
        }
    }
 
}    // om636
