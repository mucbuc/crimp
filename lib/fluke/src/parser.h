/*
	objective:
		- interpret
		- drive lexer
		- own context
		- manage/own handler
		- only operate on T, type conversion, subscriptionn... are T's job

	blocked:
		- assignment and copy constructor because of lazyness
	
	design choices:
		- composition for lexer and context to minimize dependencies 	
	
	example:
*/

#ifndef PARSER_H_8900700
#define PARSER_H_8900700

#include <functional>

#include <lib/context/context.h>

#include <src/flukefwd.h>
#include <src/lexer.h>

namespace om636
{
	namespace fluke
	{
		template<class T, class U> 
		struct parser
		{
			// types			
			typedef T analyzer_type; 
			typedef U context_type;

			virtual ~parser() = default;
			virtual context_type & interpret( analyzer_type & ) = 0;
			virtual context_type & context() = 0;
			virtual const context_type & context() const = 0;
		};

	    template<class T, class U>
		class brute_parser
		: public parser< T, U >
		{
			typedef parser< T, U > base_type;

		public:
			using typename base_type::analyzer_type;
			using typename base_type::context_type;

			// resources
			brute_parser( context_type & );
			virtual ~brute_parser() = default;
			brute_parser( const brute_parser & ) = default;
			brute_parser & operator=(const brute_parser &) = default;

			// access
			virtual context_type & context();
			virtual const context_type & context() const;

			// objective
			context_type & interpret( analyzer_type & );
		private:
			typedef typename analyzer_type::listener_type listener_type;

			context_type & m_context;
            std::vector< listener_type > m_listener;
		};
    } // fluke
}	// om636

#include "parser.hxx"

#endif // PARSER_H_8900700