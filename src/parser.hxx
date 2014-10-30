namespace om636
{
	namespace fluke
	{
		namespace fluke_private
		{
			template<class T> 
			bool is_numeric( const T & c )
			{
				enum { period = '.' };
				return isdigit(c) || c == period;
			}
		}

		/////////////////////////////////////////////////////////////////////////////////////////////
	    // parser<T> 
		/////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U>
		brute_parser<T, U>::brute_parser( context_type & c )
	    : m_context( c )
		{}

		////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U>
		auto brute_parser<T, U>::context() -> context_type &
		{	return m_context; }

		////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U>
		auto brute_parser<T, U>::context() const -> const context_type & 
		{	return m_context; }
		
		////////////////////////////////////////////////////////////////////////////////////////////
		template<class T, class U>
		auto brute_parser<T, U>::interpret(analyzer_type & analyzer) -> context_type & 
		{
			typedef typename analyzer_type::callback_type callback_type; 
			typedef typename callback_type::argument_type argument_type;

			auto onFunction( [&](const argument_type & value){
				
				using namespace std;

				typedef typename argument_type::value_type value_type; 

				value_type front( value[0] );

				enum { semicolon = ';' };
				if (fluke_private::is_numeric(front))
					analyzer.emit( "number", value );
				else if (isalpha(front))
					analyzer.emit( "word", value );
				else if (front != semicolon)
					analyzer.emit( "operator", value ); 
			} );

			m_listener.push_back( analyzer.on( " ", onFunction ) );
			m_listener.push_back( analyzer.on( "\n", onFunction ) );
			m_listener.push_back( analyzer.on( "\t", onFunction ) );
			m_listener.push_back( analyzer.on( ";", onFunction ) );

	        return context();
		}
	} 	// fluke
} 	// om636
