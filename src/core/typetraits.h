#ifdef __TYPE_TRAITS__INCLUDE_GUARD__97987979797
#define TYPE_TRAITS__INCLUDE_GUARD__97987979797

/* 
	to do:
	-	specialize type_traits for function pointers with equal argument/result types
		example:
			RET(*)(ARG) != RET(*)(RET)
*/

namespace om636
{
	template<class RET>
	struct type_traits< RET(*)() >
	{
		typedef type_tree< null_type, null_type > argument_type;
		typedef RET return_type;
	};

	template<class RET, class ARG>
	struct type_traits< RET(*)(ARG) >
	{
		typedef type_tree< ARG, null_type > argument_type;
		typedef RET return_type;
	};

	template<class RET, class ARG_1, class ARG_2>
	struct type_traits< RET(*)(ARG_1, ARG_2) >
	{
		typedef type_tree< ARG_1, ARG_2 > argument_type;
		typedef RET return_type;
	};

	template<class RET, class ARG_1, class ARG_2, class ARG_3>
	struct type_traits< RET(*)(ARG_1, ARG_2, ARG_3) >
	{
		typedef type_tree< ARG_1, type_tree< ARG_2, ARG_3 > > argument_type;
		typedef RET return_type;
	};

	// member function 
	template<class T, class RET>
	struct type_traits< RET (T::*)() >
	{
		typedef void argument_type;
		typedef void return_type;
	};

	template<class T, class RET, class ARG>
	struct type_traits< RET (T::*)(ARG) >
	{
		typedef ARG argument_type;
		typedef RET return_type;
	};

	template<class T, class RET, class ARG_1, class ARG_2>
	struct type_traits< RET (T::*)(ARG_1, ARG_2) >
	{
		typedef type_tree< ARG_1, ARG_2 > argument_type;
		typedef RET return_type;
	};

	template<class T, class RET, class ARG_1, class ARG_2, class ARG_3>
	struct type_traits< RET (T::*)(ARG_1, ARG_2, ARG_3) >
	{
		typedef type_tree< ARG_1, type_tree< ARG_2, ARG_3 > > argument_type;
		typedef RET return_type;
    };

}	// om636

#endif // __TYPE_TRAITS__INCLUDE_GUARD__97987979797