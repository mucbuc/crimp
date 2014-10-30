{
	'target_defaults': {
		'includes': [
			'plank/def/cpp11.gypi',
			'lib/traverse/def/base.gypi',
			'lib/context/def/base.gypi'
		],
		'sources': [ 
			'src/components/componentsfwd.h',
			'src/components/observer.h',
			'src/components/observer.hxx',
			'src/components/range.h',
			'src/components/subject.h',
			'src/components/subject.hxx',
			'src/core/assert.cpp', 
			'src/core/assert.h',
			'src/core/assert.hxx',
			'src/core/chain.h',
			'src/core/chain.hxx',
			'src/core/constraints.h',
			'src/core/constraints.hxx',
			'src/core/core.h',
			'src/core/core.hxx',
			'src/core/corefwd.h',
			'src/core/persistent.h',
			'src/core/persistent.hxx',
			'src/core/typetraits.h',
			'src/core/typeutills.h',
			'src/create/abstract_factory.h',
			'src/create/abstract_factory.hxx',
			'src/create/concrete_factory.h',
			'src/create/concrete_factory.hxx',
			'src/create/createfwd.h',
			'src/create/object_factory.h',
			'src/create/object_factory.hxx',
			'src/create/singleton.h',
			'src/create/singleton.hxx',
		], #sources
	}
}