namespace om636
{
    namespace Private
    {

        #pragma mark -
        #pragma mark - count_bits_impl
        #pragma mark -
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        struct count_bits_impl;

        /////////////////////////////////////////////////////////////////////////////////////////////
        template<>
        struct count_bits_impl< std::string >
        {
            size_t operator()(const std::string & s) const
            {
                typedef std::string::const_iterator iterator;
                size_t result( 0 );
                for (iterator b(s.begin()), e(s.end()); b != e; ++b)
                {
                    char tester( 1 ), value( * b );
                    do
                        if (tester & value)
                            ++result;
                    while (tester <<= 1);
                }
                
                return result;
            }
        };
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T>
        size_t count_bits(const T & s)
        {
            return count_bits_impl<T>()( s );
        }

        #pragma mark -
        #pragma mark - out_op
        #pragma mark -
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class S>
        class out_op
        {
            S & stream;
            mutable bool m_first;
            
            out_op() = delete;
            out_op & operator=(const out_op &) = delete;
        
        public:
            
            out_op(S & s) : stream(s), m_first( 1 ) {}
            out_op(const out_op & c) : stream( c.stream ), m_first( c.m_first ) {}
            
            template<class T> 
            void operator()(const T & a) const 
            { 
                ASSERT( stream );
                
                if (m_first)
                    m_first = 0; 
                else
                    stream << " ";
                stream << a;
            }
            
            template<class T, class U>
            void operator()(const std::pair<T, U> & p) const 
            {
                ASSERT( stream.good() );
                
                stream << p.first << std::endl << p.second << std::endl << count_bits( p.first ) + count_bits( p.second ) << std::endl;
            }
        };
    }
    
    #pragma mark -
    #pragma mark - persistent_raw
    #pragma mark -

    /////////////////////////////////////////////////////////////////////////////////////////////
    // persistent_raw<T>
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    const typename persistent_raw<T>::storage_type & persistent_raw<T>::storage() const
    {   return m_storage; }
        
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T> 
    typename persistent_raw<T>::storage_type & persistent_raw<T>::storage()
    {   return m_storage; }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void persistent_raw<T>::read( const char * path )
    {
        using namespace std;
        
        fstream in( path, ios_base::in ); 
        string key;
        string value;
        while (getline(in, key) && getline(in, value))
        {
            string bitcount; 
            if (getline(in, bitcount))
            {
                using Private::count_bits;
                
                stringstream temp(bitcount); 
                unsigned count; 
                temp >> count; 
                
                if (count_bits(key) + count_bits(value) == count)
                    storage()[key] = value;
            }
        }
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T> 
    void persistent_raw<T>::write( const char * path )
    {
        using namespace std;
        ofstream out( path, ios_base::out | ios_base::trunc );
        
        if (out)
            for_each( m_storage.begin(), m_storage.end(), Private::out_op<ofstream>(out) );
        else
            std::cout << "persistent error" << std::endl;
    }

    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    persistent_raw<T>::persistent_raw()
    {}
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    persistent_raw<T>::~persistent_raw()
    {}
    
    #pragma mark -
    #pragma mark - persistent
    #pragma mark -
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    // persistent
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    persistent<T>::persistent()
    : base_type()
    , m_path()
    {}
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    persistent<T>::~persistent()
    {
        if (!m_path.empty())
            write(m_path.c_str());
    }
    
    /////////////////////////////////////////////////////////////////////////////////////////////
    template<class T>
    void persistent<T>::open( const char * c_path )
    {
        const std::string path( c_path );
        if (m_path != path)
        {
            if (!m_path.empty())
                write( m_path.c_str() );
            m_path = path;
            read(m_path.c_str());
        }
    }
    
}   // om636

