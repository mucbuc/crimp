/*
tramp
Copyright (c) 2013 by Mark Busenitz
www.github.com/mucbuc

objective:
    - std::tuple traversal functions
 
dependancies:
    - std::tuple

usage: 
    - the last argument is the functor handling the elements
    - the tuples can be passed by left reference, right reference or const reference
    - '_if' versions cancel traversal if the functor returns false
    
    unary:
    - traverse::elements( tuple< a, b, c >(), f );
        ==> f( a ); f( b ); f( c );
    - traverse::combinations( tuple< a, b, c >(), f );
        ==> f( a, b ); f( a, c ); f( b, c );
    - traverse::pairs( tuple< a, b, c >(), f );
        ==> f( a ); f( a, b ); f( b, c );
    - traverse::reduce( tuple< a, b, c >(), f );
        ==> f( f( a, b ), c );
 
    binary:
    - traverse::parallel( tuple< a, b, c >(), tuple< d, e >(), f );
        ==> f( a, d ); f( b, e );
    - traverse::combinations( tuple< a, b, c >(), tuple< d, e >(), f );
        ==> f( a, d ); f( a, e ); f( b, d ); f( b, e ); f( c, d ); f( c, e );
 
todo: 
    - test

 */

#ifndef TRAVERSE_H__emhAd95QCGblkZVTxDygf3upPMocRq
#define TRAVERSE_H__emhAd95QCGblkZVTxDygf3upPMocRq

#include <tuple>

namespace om636
{
    namespace traverse
    {

    //  unary
        template<class T, class U> U elements(T &, U);
        template<class T, class U> U elements(T &&, U);
        template<class T, class U> U elements(const T &, U);
        
        template<class T, class U> U elements_if(T &, U);
        template<class T, class U> U elements_if(T &&, U);
        template<class T, class U> U elements_if(const T &, U);

        template<class T, class U> U combinations(T &, U);
        template<class T, class U> U combinations(T &&, U);
        template<class T, class U> U combinations(const T &, U);
        
        template<class T, class U> U combinations_if(T &, U);
        template<class T, class U> U combinations_if(T &&, U);
        template<class T, class U> U combinations_if(const T &, U);

        template<class T, class U> U pairs(T &, U);
        template<class T, class U> U pairs(T &&, U);
        template<class T, class U> U pairs(const T &, U);
        
        template<class T, class U> U pairs_if(T &, U);
        template<class T, class U> U pairs_if(T &&, U);
        template<class T, class U> U pairs_if(const T &, U);
        
        template<class T, class U, class V> std::tuple<T, V> reduce(U &, V);
        template<class T, class U, class V> std::tuple<T, V> reduce(U &&, V);
        template<class T, class U, class V> std::tuple<T, V> reduce(const U &, V);
        
    //  binary
        template<class T, class V> V parallel(T &, T &, V);
        template<class T, class V> V parallel(T &, T &&, V);
        template<class T, class V> V parallel(T &, const T &, V);
        
        template<class T, class V> V parallel(T &&, T &, V);
        template<class T, class V> V parallel(T &&, T &&, V);
        template<class T, class V> V parallel(T &&, const T &, V);
        
        template<class T, class V> V parallel(const T &, T &, V);
        template<class T, class V> V parallel(const T &, T &&, V);
        template<class T, class V> V parallel(const T &, const T &, V);
        
        template<class T, class U, class V> V parallel(T &, U &, V);
        template<class T, class U, class V> V parallel(T &, U &&, V);
        template<class T, class U, class V> V parallel(T &, const U &, V);
        
        template<class T, class U, class V> V parallel(T &&, U &, V);
        template<class T, class U, class V> V parallel(T &&, U &&, V);
        template<class T, class U, class V> V parallel(T &&, const U &&, V);
        
        template<class T, class U, class V> V parallel(const T &, U &, V);
        template<class T, class U, class V> V parallel(const T &, U &&, V);
        template<class T, class U, class V> V parallel(const T &, const U &&, V);
        
        template<class T, class V> V parallel_if(T &, T &, V);
        template<class T, class V> V parallel_if(T &, T &&, V);
        template<class T, class V> V parallel_if(T &, const T &, V);
        
        template<class T, class V> V parallel_if(T &&, T &, V);
        template<class T, class V> V parallel_if(T &&, T &&, V);
        template<class T, class V> V parallel_if(T &&, const T &, V);
        
        template<class T, class V> V parallel_if(const T &, T &, V);
        template<class T, class V> V parallel_if(const T &, T &&, V);
        template<class T, class V> V parallel_if(const T &, const T &, V);
        
        template<class T, class U, class V> V parallel_if(T &, U &, V);
        template<class T, class U, class V> V parallel_if(T &, U &&, V);
        template<class T, class U, class V> V parallel_if(T &, const U &, V);
        
        template<class T, class U, class V> V parallel_if(T &&, U &, V);
        template<class T, class U, class V> V parallel_if(T &&, U &&, V);
        template<class T, class U, class V> V parallel_if(T &&, const U &&, V);
        
        template<class T, class U, class V> V parallel_if(const T &, U &, V);
        template<class T, class U, class V> V parallel_if(const T &, U &&, V);
        template<class T, class U, class V> V parallel_if(const T &, const U &, V);
        
        template<class T, class V> V combinations(T &, T &, V);
        template<class T, class V> V combinations(T &, T &&, V);
        template<class T, class V> V combinations(T &, const T &, V);
        
        template<class T, class V> V combinations(T &&, T &, V);
        template<class T, class V> V combinations(T &&, T &&, V);
        template<class T, class V> V combinations(T &&, const T &, V);
        
        template<class T, class V> V combinations(const T &, T &, V);
        template<class T, class V> V combinations(const T &, T &&, V);
        template<class T, class V> V combinations(const T &, const T &, V);
        
        template<class T, class U, class V> V combinations(T &, U &, V);
        template<class T, class U, class V> V combinations(T &, U &&, V);
        template<class T, class U, class V> V combinations(T &, const U &, V);
        
        template<class T, class U, class V> V combinations(T &&, U &, V);
        template<class T, class U, class V> V combinations(T &&, U &&, V);
        template<class T, class U, class V> V combinations(T &&, const U &&, V);
        
        template<class T, class U, class V> V combinations(const T &, U &, V);
        template<class T, class U, class V> V combinations(const T &, U &&, V);
        template<class T, class U, class V> V combinations(const T &, const U &&, V);
        
        template<class T, class V> V combinations_if(T &, T &, V);
        template<class T, class V> V combinations_if(T &, T &&, V);
        template<class T, class V> V combinations_if(T &, const T &, V);
        
        template<class T, class V> V combinations_if(T &&, T &, V);
        template<class T, class V> V combinations_if(T &&, T &&, V);
        template<class T, class V> V combinations_if(T &&, const T &, V);
        
        template<class T, class V> V combinations_if(const T &, T &, V);
        template<class T, class V> V combinations_if(const T &, T &&, V);
        template<class T, class V> V combinations_if(const T &, const T &, V);
        
        template<class T, class U, class V> V combinations_if(T &, U &, V);
        template<class T, class U, class V> V combinations_if(T &, U &&, V);
        template<class T, class U, class V> V combinations_if(T &, const U &, V);
        
        template<class T, class U, class V> V combinations_if(T &&, U &, V);
        template<class T, class U, class V> V combinations_if(T &&, U &&, V);
        template<class T, class U, class V> V combinations_if(T &&, const U &&, V);
        
        template<class T, class U, class V> V combinations_if(const T &, U &, V);
        template<class T, class U, class V> V combinations_if(const T &, U &&, V);
        template<class T, class U, class V> V combinations_if(const T &, const U &, V);
    }   // traverse
}   //  om636

#include "interface.hxx"

#endif // __TRAVERSE_H__emhAd95QCGblkZVTxDygf3upPMocRq
