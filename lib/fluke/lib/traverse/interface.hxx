/*
Copyright (c) 2013 by Mark Busenitz
www.github.com/mucbuc
*/

namespace om636
{
    namespace traverse
    {
        namespace Private
        {
            // elements_impl
            template<int, int, class>
            struct elements_impl;
            
            template<int M, class T>
            struct elements_impl< M, M, T >;
            
            
            // combinations_impl
            template<int, int, int, class >
            struct combinations_impl;
            
            template<int M, int N, class T>
            struct combinations_impl< M, N, N, T >;
            
            template<int M, int N, class T >
            struct combinations_impl< M, N, M, T >;
            

            // pairs_impl
            template<int, int, class>
            struct pairs_impl;
            
            template<int M, class T>
            struct pairs_impl< 2, M, T>;
            
            template<int M, class T>
            struct pairs_impl< M, M, T>;
            
            template<class T>
            struct pairs_impl<2, 2, T>;
            
            template<class T>
            struct pairs_impl<2, 1, T>;
            
            
            // reduce_impl
            template<int, int, class, class>
            struct reduce_impl;
            
            template<int M, class T, class U>
            struct reduce_impl< M, M, T, U>;
            
            template<class T, class U>
            struct reduce_impl<2, 1, T, U>;
            
            
            // parallel_impl
            template<int, int, class, class>
            struct parallel_impl;
            
            template<int M, class T, class U>
            struct parallel_impl< M, M, T, U >;
            
            
            // combinations_binary_impl
            template<int, int, int, int, class, class>
            struct combinations_binary_impl;
            
            template<int M, int N, int O, class T, class U>
            struct combinations_binary_impl< M, N, O, N, T, U >;
            
            template<int M, int N, int O, class T, class U>
            struct combinations_binary_impl< M, N, M, O, T, U >;
            
        }   // Private

        //////////////////////// /////////////////////////////////////////////////////////////////////
        template<class T, class U>
        U elements(T & t, U visitor)
        {
            return Private::elements_impl< 0, std::tuple_size<T>::value, T & >::visit( t, visitor );
        }

        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        U elements(T && t, U visitor)
        {
            return Private::elements_impl< 0, std::tuple_size<T>::value, T && >::visit( t, visitor );
        }

        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U> U elements(const T & t, U visitor)
        {
            return Private::elements_impl< 0, std::tuple_size<T>::value, const T & >::visit( t, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        U elements_if(T & t, U visitor)
        {
            return Private::elements_impl< 0, std::tuple_size<T>::value, T >::visit_if( t, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        U elements_if(T && t, U visitor)
        {
            return Private::elements_impl< 0, std::tuple_size<T>::value, T && >::visit_if( t, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        U elements_if(const T & t, U visitor)
        {
            return Private::elements_impl< 0, std::tuple_size<T>::value, const T & >::visit_if( t, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        U combinations(T & t, U visitor)
        {
            return Private::combinations_impl< 0, 1, std::tuple_size<T>::value, T & >::visit( t, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        U combinations(T && t, U visitor)
        {
            return Private::combinations_impl< 0, 1, std::tuple_size<T>::value, T && >::visit( t, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        U combinations(const T & t, U visitor)
        {
            return Private::combinations_impl< 0, 1, std::tuple_size<T>::value, const T & >::visit( t, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        U combinations_if(T & t, U visitor)
        {
            return Private::combinations_impl< 0, 1, std::tuple_size<T>::value, T & >::visit_if( t, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        U combinations_if(T && t, U visitor)
        {
            return Private::combinations_impl< 0, 1, std::tuple_size<T>::value, T && >::visit_if( t, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        U combinations_if(const T & t, U visitor)
        {
            return Private::combinations_impl< 0, 1, std::tuple_size<T>::value, const T & >::visit_if( t, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        U pairs(T & t, U visitor)
        {
            return Private::pairs_impl< 2, std::tuple_size<T>::value, T & >::visit( t, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        U pairs(T && t, U visitor)
        {
            return Private::pairs_impl< 2, std::tuple_size<T>::value, T && >::visit( t, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        U pairs(const T & t, U visitor)
        {
            return Private::pairs_impl< 2, std::tuple_size<T>::value, const T & >::visit( t, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        U pairs_if(T & t, U visitor)
        {
            return Private::pairs_impl< 2, std::tuple_size<T>::value, T & >::visit_if( t, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        U pairs_if(T && t, U visitor)
        {
            return Private::pairs_impl< 2, std::tuple_size<T>::value, T && >::visit_if( t, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U>
        U pairs_if(const T & t, U visitor)
        {
            return Private::pairs_impl< 2, std::tuple_size<T>::value, const T & >::visit_if( t, visitor );
        }

        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        std::tuple<T, V> reduce(U & t, V visitor)
        {
            return Private::reduce_impl< 2, std::tuple_size<U>::value, T, U & >::visit( t, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        std::tuple<T, V> reduce(U && t, V visitor)
        {
            return Private::reduce_impl< 2, std::tuple_size<U>::value, T, U && >::visit( t, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        std::tuple<T, V> reduce(const U & t, V visitor)
        {
            return Private::reduce_impl< 2, std::tuple_size<U>::value, T, const U & >::visit( t, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V parallel(T & lhs, T & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &, T & >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V parallel(T & lhs, T && rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &, T && >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V parallel(T & lhs, const T & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &, const T & >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V parallel(T && lhs, T & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &&, T & >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V parallel(T && lhs, T && rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &&, T && >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V parallel(T && lhs, const T & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &&, const T & >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V parallel(const T & lhs, T & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, const T &, T & >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V parallel(const T & lhs, T && rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, const T &, T && >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V parallel(const T & lhs, const T & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, const T &, const T & >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V parallel(T & lhs, U & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &, U & >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V parallel(T & lhs, U && rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &, U && >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V parallel(T & lhs, const U & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &, const U & >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V parallel(T && lhs, U & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &&, U & >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V parallel(T && lhs, U && rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &&, U && >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V parallel(T && lhs, const U & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &&, const U & >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V parallel(const T & lhs, U & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, const T &, U & >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V parallel(const T & lhs, U && rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, const T &, U && >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V parallel(const T & lhs, const U & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, const T &, const U & >::visit( lhs, rhs, visitor );
        }

        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V parallel_if(T & lhs, T & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &, T & >::visit_if( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V parallel_if(T & lhs, T && rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &, T && >::visit_if( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V parallel_if(T & lhs, const T & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &, const T & >::visit_if( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V parallel_if(T && lhs, T & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &&, T & >::visit_if( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V parallel_if(T && lhs, T && rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &&, T && >::visit_if( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V parallel_if(T && lhs, const T & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &&, const T & >::visit_if( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V parallel_if(const T & lhs, T & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, const T &, T & >::visit_if( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V parallel_if(const T & lhs, T && rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, const T &, T && >::visit_if( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V parallel_if(const T & lhs, const T & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, const T &, const T & >::visit_if( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V parallel_if(T & lhs, U & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &, U & >::visit_if( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V parallel_if(T & lhs, U && rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &, U && >::visit_if( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V parallel_if(T & lhs, const U & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &, const U & >::visit_if( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V parallel_if(T && lhs, U & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &&, U & >::visit_if( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V parallel_if(T && lhs, U && rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &&, U && >::visit_if( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V parallel_if(T && lhs, const U & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, T &&, const U & >::visit_if( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V parallel_if(const T & lhs, U & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, const T &, U & >::visit_if( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V parallel_if(const T & lhs, U && rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, const T &, U && >::visit_if( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V parallel_if(const T & lhs, const U & rhs, V visitor )
        {
            return Private::parallel_impl< 0, std::tuple_size<T>::value, const T &, const U & >::visit_if( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V combinations(T & lhs, T & rhs, V visitor)
        {
            return Private::combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &, T & >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V combinations(T & lhs, T && rhs, V visitor)
        {
            return Private::combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &, T && >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V combinations(T & lhs, const T & rhs, V visitor)
        {
            return Private::combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &, const T & >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V combinations(T && lhs, T & rhs, V visitor)
        {
            return Private::combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &&, T & >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V combinations(T && lhs, T && rhs, V visitor)
        {
            return Private::combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &&, T && >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V combinations(T && lhs, const T & rhs, V visitor)
        {
            return Private::combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &&, const T & >::visit( lhs, rhs, visitor );
        }
     
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V combinations(const T & lhs, T & rhs, V visitor)
        {
            return Private::combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, const T &, T & >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V combinations(const T & lhs, T && rhs, V visitor)
        {
            return Private::combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, const T &, T && >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class V>
        V combinations(const T & lhs, const T & rhs, V visitor)
        {
            return Private::combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, const T &, const T & >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V combinations(T & lhs, U & rhs, V visitor)
        {
            return Private::combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &, U & >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V combinations(T & lhs, U && rhs, V visitor)
        {
            return Private::combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &, U && >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V combinations(T & lhs, const U & rhs, V visitor)
        {
            return Private::combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &, const U & >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V combinations(T && lhs, U & rhs, V visitor)
        {
            return Private::combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &&, U & >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V combinations(T && lhs, U && rhs, V visitor)
        {
            return Private::combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &&, U && >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V combinations(T && lhs, const U & rhs, V visitor)
        {
            return Private::combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, T &&, const U & >::visit( lhs, rhs, visitor );
        }
        
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V combinations(const T & lhs, U & rhs, V visitor)
        {
            return Private::combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, const T &, U & >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V combinations(const T & lhs, U && rhs, V visitor)
        {
            return Private::combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, const T &, U && >::visit( lhs, rhs, visitor );
        }
        
        /////////////////////////////////////////////////////////////////////////////////////////////
        template<class T, class U, class V>
        V combinations(const T & lhs, const U & rhs, V visitor)
        {
            return Private::combinations_binary_impl< 0, 0, std::tuple_size< T >::value, std::tuple_size< T >::value, const T &, const U & >::visit( lhs, rhs, visitor );
        }

        namespace Private
        {
            
    #pragma mark - elements_impl
            
            /////////////////////////////////////////////////////////////////////////////////////////////
            // elements_impl
            /////////////////////////////////////////////////////////////////////////////////////////////
            template<int M, int N, class T>
            struct elements_impl
            {
                enum { index = M, size = N };
                typedef elements_impl< index + 1, size, T > permutation;
                
                template<class U>
                static U visit( T t, U visitor )
                {
                    visitor( std::get< index >(t) );
                    return permutation::visit( t, visitor );
                }
                
                template<class U>
                static U visit_if( T t, U visitor )
                {
                    if (visitor( std::get< N >(t) ) )
                        return permutation::visit( t, visitor );
                    return visitor;
                }
            };
            
            /////////////////////////////////////////////////////////////////////////////////////////////
            template<int M, class T>
            struct elements_impl< M, M, T >
            {
                template<class U>
                static U visit( T, U visitor )
                {   return visitor; }
                
                template<class U>
                static U visit_if( T, U visitor )
                {   return visitor; }
            };
            
    #pragma mark - combinations_impl
            
            /////////////////////////////////////////////////////////////////////////////////////////////
            // combinations_impl
            /////////////////////////////////////////////////////////////////////////////////////////////
            template<int M, int N, int L, class T >
            struct combinations_impl
            {
                enum { l_index = M, r_index = N, size = L };
                typedef combinations_impl< l_index, r_index + 1, size, T > permutation;
                
                template<class U>
                static U visit( T t, U visitor )
                {
                    using std::get;
                    visitor( get< N >(t), get< M >(t) );
                    return permutation::visit( t, visitor );
                }
                
                template<class U>
                static U visit_if( T t, U visitor )
                {
                    using std::get;
                    if (visitor( get< N >(t), get< M >(t) ) )
                        return permutation::visit_if( t, visitor );
                    return visitor;
                }
            };
            
            /////////////////////////////////////////////////////////////////////////////////////////////
            template<int M, int N, class T>
            struct combinations_impl< M, N, N, T >
            {
                enum { l_index = M, r_index = N, size = N };
                typedef combinations_impl< l_index + 1, l_index + 2, size, T > permutation;
                
                template<class U>
                static U visit( T t, U visitor )
                {   return permutation::visit( t, visitor );    }
                
                template<class U>
                static U visit_if( T t, U visitor )
                {   return permutation::visit_if( t, visitor ); }
            };
            
            /////////////////////////////////////////////////////////////////////////////////////////////
            template<int M, int N, class T >
            struct combinations_impl< M, N, M, T >
            {
                template<class U>
                static U visit( T, U visitor )
                {   return visitor; }
                
                template<class U>
                static U visit_if( T, U visitor )
                {   return visitor; }
            };
            
    #pragma mark - pairs_impl
            
            /////////////////////////////////////////////////////////////////////////////////////////////
            // pairs_impl
            /////////////////////////////////////////////////////////////////////////////////////////////
            template<int M, int N, class T>
            struct pairs_impl
            {
                enum { index = M, size = N };
                typedef pairs_impl< index + 1, size, T> permutation;
                
                template<class U>
                static U visit(T t, U visitor )
                {
                    using namespace std;
                    visitor( get< index - 2 >(t), get< index - 1 >(t) );
                    return permutation::visit( t, visitor );
                }
                
                template<class U>
                static U visit_if(T t, U visitor )
                {
                    using namespace std;
                    if (visitor( get< index - 2 >(t), get< index - 1 >(t)))
                        return permutation::visit_if( t, visitor );
                    return visitor;
                }
            };
            
            /////////////////////////////////////////////////////////////////////////////////////////////
            template<int M, class T>
            struct pairs_impl<2, M, T>
            {
                enum { index = 2, size = M };
                typedef pairs_impl< index + 1, size, T> permutation;
                
                template<class U>
                static U visit( T t, U visitor )
                {
                    using namespace std;
                    auto o( get< 0 >(t) );
                    visitor( o );
                    visitor( o, get< 1 >(t) );
                    return permutation::visit( t, visitor );
                }
                
                template<class U>
                static U visit_if( T t, U visitor )
                {
                    using namespace std;
                    auto o( get< 0 >(t) );
                    if ( visitor( o ) &&  visitor( o, get< 1 >(t) ) )
                        return permutation::visit_if( t, visitor );
                    return visitor;
                }
            };
            
            /////////////////////////////////////////////////////////////////////////////////////////////
            template<int M, class T>
            struct pairs_impl<M, M, T>
            {
                enum { index = M, size = M };
                
                template<class U>
                static U visit( T t, U visitor )
                {
                    using namespace std;
                    visitor( get< index - 2 >(t), get< index - 1 >(t) );
                    return visitor;
                }
                
                template<class U>
                static U visit_if( T t, U visitor )
                {
                    return visit( t, visitor );
                }
            };

            /////////////////////////////////////////////////////////////////////////////////////////////
            template<class T>
            struct pairs_impl<2, 2, T>
            {
                enum { index = 2, size = 2 };
                typedef pairs_impl< index + 1, size, T> permutation;
                
                template<class U>
                static U visit( T t, U visitor )
                {
                    using namespace std;
                    auto o( get< 0 >(t) );
                    visitor( o );
                    visitor( o, get< 1 >(t) );
                    return visitor;
                }

                template<class U>
                static U visit_if( T t, U visitor )
                {
                    using namespace std;
                    auto o( get< 0 >(t) );
                    if (visitor( o ))
                        visitor( o, get< 1 >(t) );
                    return visitor;
                }
            };
            
            /////////////////////////////////////////////////////////////////////////////////////////////
            template<class T>
            struct pairs_impl<2, 1, T>
            {
                enum { index = 2, size = 1 };
                
                template<class U>
                static U visit( T t, U visitor )
                {
                    visitor( std::get< 0 >(t) );
                    return visitor;
                }
                
                template<class U>
                static U visit_if( T t, U visitor )
                {
                    return visit( t, visitor );
                }
            };
            
    #pragma mark - reduce_impl
            
            /////////////////////////////////////////////////////////////////////////////////////////////
            // reduce_impl
            /////////////////////////////////////////////////////////////////////////////////////////////
            template<int M, int N, class T, class U>
            struct reduce_impl
            {
                enum { index = M, size = N };
                typedef reduce_impl< index + 1, size, T, U> permutation;
                
                template<class V>
                static std::tuple<T, V> visit(U t, V visitor )
                {
                    using namespace std;
                    
                    tuple<T, V> r( permutation::visit( t, visitor ) );
                    visitor = get<1>(r);
                    T value( visitor( get< index - 2 >(t), get< 0 >(r) ) );
                    return make_tuple( value, visitor );
                }
            };
            
            /////////////////////////////////////////////////////////////////////////////////////////////
            template<int M, class T, class U>
            struct reduce_impl<M, M, T, U>
            {
                enum { index = M, size = M };
                
                template<class V>
                static std::tuple<T, V> visit( U t, V visitor )
                {
                    using namespace std;
                    T value( visitor( get< index - 2 >(t), get< index - 1 >(t) ) );
                    return make_tuple( value, visitor );
                }
            };
            
            /////////////////////////////////////////////////////////////////////////////////////////////
            template<class T, class U>
            struct reduce_impl<2, 1, T, U>
            {
                template<class V>
                static std::tuple<T, V> visit( U t, V visitor )
                {
                    using namespace std;
                    T value( visitor( get< 0 >(t) ) );
                    return make_tuple( value, visitor );
                }
            };
            
    #pragma mark - parallel_impl
            
            /////////////////////////////////////////////////////////////////////////////////////////////
            // parallel_impl
            /////////////////////////////////////////////////////////////////////////////////////////////
            template<int M, int N, class T, class U>
            struct parallel_impl
            {
                enum { index = M, size = N };
                typedef parallel_impl< index + 1, size, T, U > permutation;
                
                template<class V>
                static V visit( T lhs, U rhs, V visitor )
                {
                    using namespace std;
                    visitor( get< index >(lhs), get< index >(rhs) );
                    return permutation::visit( lhs, rhs, visitor );
                }
                
                template<class V>
                static V visit_if( T lhs, U rhs, V visitor )
                {
                    using namespace std;
                    visitor( get< index >(lhs), get< index >(rhs) );
                    return permutation::visit_if( lhs, rhs, visitor );
                }
            };
            
            /////////////////////////////////////////////////////////////////////////////////////////////
            template<int M, class T, class U>
            struct parallel_impl< M, M, T, U >
            {
                template<class V>
                static V visit( T, U, V visitor )
                {   return visitor; }
                
                template<class V>
                static V visit_if( T, U, V visitor )
                {   return visitor; }
            };
            
    #pragma mark - combinations_binary_impl
            
            /////////////////////////////////////////////////////////////////////////////////////////////
            // combinations_binary_impl
            /////////////////////////////////////////////////////////////////////////////////////////////
            template<int M, int N, int O, int P, class T, class U>
            struct combinations_binary_impl
            {
                enum { l_index = M, r_index = N, l_size = O, r_size = P };
                typedef combinations_binary_impl< l_index, r_index + 1, l_size, r_size, T, U > permutation;
                
                template<class V>
                static V visit( T lhs, U rhs, V visitor )
                {
                    using namespace std;
                    visitor( get< l_index >(lhs), get< r_index >(rhs) );
                    return permutation::visit( lhs, rhs, visitor );
                }
            };
            
            /////////////////////////////////////////////////////////////////////////////////////////////
            template<int M, int N, int O, class T, class U>
            struct combinations_binary_impl< M, N, O, N, T, U >
            {
                enum { l_index = M, r_index = N, l_size = O, r_size = N };
                typedef combinations_binary_impl< l_index + 1, 0, l_size, r_size, T, U > permutation;
                
                template<class V>
                static V visit( T lhs, U rhs, V visitor )
                {   return permutation::visit( lhs, rhs, visitor ); }
            };
            
            /////////////////////////////////////////////////////////////////////////////////////////////
            template<int M, int N, int O, class T, class U>
            struct combinations_binary_impl< M, N, M, O, T, U >
            {
                template< class V>
                static V visit( T, U, V visitor )
                {   return visitor; }
            };
            
        }   // Private
    }   // traverse 

} // om636