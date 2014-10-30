#objective:
  * std::tuple traversal functions
 
#dependancies:
  * std::tuple

#usage:
  * the last argument is the functor handling the elements
  * the tuples can be passed by left reference, right reference or const reference
  * '_if' versions cancel traversal if the functor returns false
    
######unary:
  * `traverse::elements( tuple< a, b, c >(), f );`  
  => `f( a );` `f( b );` `f( c );`
  * `traverse::combinations( tuple< a, b, c >(), f );`  
  => `f( a, b );` `f( a, c );` `f( b, c );`
  * `traverse::pairs( tuple< a, b, c >(), f );`  
  => `f( a );` `f( a, b );` `f( b, c );`
  * `traverse::reduce( tuple< a, b, c >(), f );`  
  => `f( f( a, b ), c );`
 
######binary:
  * `traverse::parallel( tuple< a, b, c >(), tuple< d, e >(), f );`  
  => `f( a, d );` `f( b, e );`
  * `traverse::combinations( tuple< a, b, c >(), tuple< d, e >(), f );`  
  => `f( a, d );` `f( a, e );` `f( b, d );` `f( b, e );` `f( c, d );` `f( c, e );`
 
