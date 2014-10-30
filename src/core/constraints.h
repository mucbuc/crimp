/* 
 
objective: 
    compile time checks to improve build error messages 
*/ 

#ifndef _CONSTRAINTS_H_8900700
	#define _CONSTRAINTS_H_8900700

namespace om636
{
    namespace can_do
    {
    
        template<class T, class U>
        class arithmetic
        {
            static void constraints(T, U);
            
        public:	
            arithmetic();
        };

        template<class T, class U> 
        class read_stream
        {
            static void constraints(T, U);
            
        public:
            read_stream();
        };
        
        template<class T, class U> 
        class write_stream
        {
            static void constraints(T, U);
            
        public:
            write_stream();
        };
    }
}

#include "constraints.hxx"

#endif // _CONSTRAINTS_H_8900700