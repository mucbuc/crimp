/*
om636
Copyright (c) 2013 by Mark Busenitz
www.github.com/mucbuc

objective: 
    - define abstract interface
    - 
 
*/

#ifndef OBSERVER_H__cIuO6MV2doHZDmg8ijr17zB0YCelG3
#define OBSERVER_H__cIuO6MV2doHZDmg8ijr17zB0YCelG3

namespace om636
{

    template<class T>
	struct observer
	{
		// types
		typedef T context_type;

		virtual ~observer();
        virtual void on_swap(const context_type &, const context_type &) = 0;
        virtual void detach(void *) = 0;
	}; 

}	// om636

#include "observer.hxx"
#endif // __OBSERVER_H__cIuO6MV2doHZDmg8ijr17zB0YCelG3