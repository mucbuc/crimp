{
	'includes':[
		'lib/twice-size/twice-size.gypi',
		'plank/def/cpp11.gypi'
	],
	'target_defaults': {
		'sources': [
			'src/agent.h',
			'src/agent.hxx',
			'src/emitter.h',
			'src/emitter.hxx',
			'src/listener.h',
			'src/listener.hxx',
			'src/quemitter.h',
			'src/quemitter.hxx'
		],
	}
}