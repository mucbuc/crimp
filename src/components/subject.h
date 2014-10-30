/* 
om636
Copyright (c) 2013 by Mark Busenitz
www.github.com/mucbuc

objective: 
    collection of subject policies

*/ 

#ifndef SUBJECT_H__3OinTKlusSf57wk9G41geIdYXzUEVv
#define SUBJECT_H__3OinTKlusSf57wk9G41geIdYXzUEVv

#include <lib/context/interface.h>
#include <src/core/persistent.h>
#include <src/create/singleton.h>

#include <vector> 
#include <map>

namespace om636
{
    // no attach/detach while update
    template<class T, template<class> class U>
    struct basic_subject
    : default_subject::policy< T >
    {
        typedef T context_type;
        typedef typename default_subject::traits<context_type>::value_type value_type;
        typedef U< context_type > * observer_type;

        basic_subject();
        virtual ~basic_subject();
        void attach(const observer_type &);
		void detach(const observer_type &);
        virtual void on_swap(context_type &, context_type &);
        
        template<class V>
        static value_type on_init(V &);
        
        template<class V, class W>
        static value_type on_init(V &, const W &);
        
        template<class V>
        static V to_value(const context_type &);

    protected:
        
        typedef std::vector< observer_type > container_type;
        typedef typename container_type::iterator iterator;
        
        container_type m_observers;
    };
    

    template<class T>
    struct safe_subject
    : public T
    {
        struct locked
        {};
        
        typedef T base_type;
        using typename base_type::context_type;
        using typename base_type::observer_type;
        
        safe_subject();
        virtual ~safe_subject();
        
        void attach(const observer_type &);
        void detach(const observer_type &);
        virtual void on_swap(context_type &, context_type &);
        
    private:
        bool m_locked;
    };
    
    template<class T>
    struct state_subject
    : private T
    {
        // types
        typedef T policy_type;
        
        typedef typename policy_type::value_type value_type;
        typedef typename policy_type::context_type context_type;
        using policy_type::on_init;
        using policy_type::to_value;
        using policy_type::state;
        
        virtual ~state_subject();
        
        // comparisons
        virtual bool on_equal(const context_type &, const context_type &) const;
        virtual int on_cmp(const context_type &, const context_type &) const;
        virtual int on_sign(const context_type &) const;
        
        // modifiers
        virtual bool on_swap(context_type &, context_type &) const;
        virtual void on_add(context_type &, const context_type &) const;
        virtual void on_subtract(context_type &, const context_type &) const;
        virtual void on_mult(context_type &, const context_type &) const;
        virtual void on_divide(context_type &, const context_type &) const;
        virtual void on_remainder(context_type &, const context_type &) const;
        virtual void on_inc(context_type &) const;
        virtual void on_dec(context_type &) const;
        virtual void on_invert(context_type &) const;
    };

        

#if 0
    // abstract interface
	template<class T>
    struct subject
	{
		typedef T context_type;
        typedef observer< context_type > * observer_type;
        
		virtual ~subject();
		virtual void attach( const observer_type & ) = 0;
		virtual void detach( const observer_type & ) = 0;
        
        // note: no update while update due to const context &
        // con: this is too specific, what about a design where observer
        // 	 	returns a bool if intererested in further updates (to avoid finds)?
        //
        virtual void on_swap( context_type &, context_type & ) = 0;
    };
    
    template<class T, class U>
    struct default_policy
    {
        typedef T value_type;   // <= this gets passed up to host
        typedef U context_type;
        typedef observer< context_type > * observer_type;
        
        static void on_attach(context_type & c, const observer_type & o)
        {
            observers( c ).push_back(o);
        }
		static void on_detach(context_type & c, const observer_type & o)
        {
            observers( c ).erase( ... );
        }
        static void on_swap(context_type &, context_type &)
        {
            observers( c ).traverse( ... );
        }
    };
    
    template<class T>
    struct subject_traits
    {
        typedef T context_type;
        typedef observer< context_type > * observer_type;
        static observer_type * & state(context_type &);
        static observer_type * state(const context_type &);
    };

    template<class T>
    abstract_policy
    {
        typedef T context_type;
        typedef observer< context_type > * observer_type;
        
        virtual void on_swap(context_type &, context_type &) = 0;
        virtual void on_attach(context_type &, const observer_type &) = 0;
        virtual void on_detach(context_type &, const observer_type &) = 0;
    };
    
    template<class T, class U>
    struct state_policy
    : subject_traits< U > 
    {
        typedef typename tuple_append< T, abstract_policy * >::type value_type;   // <= this gets passed up to host
        typedef U context_type;
        typedef observer< context_type > * observer_type;
        
        static void on_attach(context_type & c, const observer_type & o)
        {
            state( c )->on_attach( c, o );
        }
		
        static void on_detach(context_type & c, const observer_type & o)
        {
            state( c )->on_detach( c, o );
        }
        
        static void on_swap(context_type & l, context_type & l)
        {
            // note: the actual call to the observer must use ( std::get<0>(l), std::get<0>(r) )
            state( c )->on_swap( l, r );
        }
    };

    /*
     the nice thing about this design is that a state pointer inside of
     context can be set to differenet handlers. base this on the number 
     model.
     */
    
#endif
    
}	// om636

#include "subject.hxx"
#endif // SUBJECT_H__3OinTKlusSf57wk9G41geIdYXzUEVv