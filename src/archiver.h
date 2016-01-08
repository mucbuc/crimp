#ifndef ARCHIVER_INCLUDE_GUARD_03K9027KSIQ
#define ARCHIVER_INCLUDE_GUARD_03K9027KSIQ

#include <iostream>

namespace private_assert
{
	struct archiver
	{
		static archiver & instance();

		~archiver();

		void pass();
		void fail( 
			const char *, 
			int, 
            const char * function, 
            const char * = "");
	private: 
		std::size_t passed = 0;
	};
}

#endif // ARCHIVER_INCLUDE_GUARD_03K9027KSIQ