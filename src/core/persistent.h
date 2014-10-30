#ifndef PERSISTENT_H_INCLUDE_GUARD_543543HHGH
#define PERSISTENT_H_INCLUDE_GUARD_543543HHGH

#include <fstream>
#include <sstream>

namespace om636
{
    template<class T> 
    class persistent_raw
    {
    public:
        
        // types
        typedef T storage_type; 
        typedef typename storage_type::iterator iterator; 
        
        persistent_raw( const persistent_raw & ) = delete;
        persistent_raw & operator=(persistent_raw) = delete;
     
        const storage_type & storage() const;
        storage_type & storage();

        persistent_raw();
        virtual ~persistent_raw();
    
    protected:
        
        void read(const char *);
        void write(const char *);
        
    private:

        storage_type m_storage;
    };
    
    template<class T>
    class persistent
    : public persistent_raw< T >
    {
    public:
        typedef persistent_raw< T > base_type;
        
        persistent();
        virtual ~persistent();
        
        void open( const char * );
    
    private:
        
        using base_type::read;
        using base_type::write;
        
        std::string m_path;
    };
    
    namespace Private
    {
        template<class T>
        struct count_bits_impl;
        
        template<class T>
        size_t count_bits(const T & s);
        
        template<class>
        class out_op; 
        
    } // Private
   
}   // om636

#include "persistent.hxx"

#endif // PERSISTENT_H_INCLUDE_GUARD_543543HHGH
