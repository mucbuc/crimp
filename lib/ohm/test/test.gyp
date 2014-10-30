{
	'includes':[
		'../ohm.gypi',
		'../plank/def/mac-targets.gypi'
	],#inclues
	'target_defaults': {
		'target_name': 'test',
		'type': 'executable',
		'sources': [
			'../test/src/emitter.cpp',
			'../test/src/emitter.h',
			'../test/src/emitter_fwd.h',
		], #sources
		'include_dirs': [
			'../plank/src/',
			'../'
		], #include_dirs		
	}, #target_defaults
}