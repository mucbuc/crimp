#ifndef FLUKEFWD_H__51m8XohpWnKJ7YMkUePLSu6IC3ZEsO
#define FLUKEFWD_H__51m8XohpWnKJ7YMkUePLSu6IC3ZEsO

#include <set> 
#include <string> 

namespace om636
{
	namespace fluke
	{
		// lexer.h
		template<class T, class U> 
		struct lexer;

		template< class T, class U, class V = std::set< std::string > >
		class brute_lexer;
	}
}

#endif // FLUKEFWD_H__51m8XohpWnKJ7YMkUePLSu6IC3ZEsO