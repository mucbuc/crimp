{
	'includes':[
		'../fluke.gypi',
		'../plank/def/mac-targets.gypi'
	],#inclues
	'target_defaults': {
		'target_name': 'test', 
		'type': 'executable',
		'sources': [
			'../test/src/main.cpp',
			'../test/src/test.h'
		], #sources
		'include_dirs': [
			'../plank/src/',
			'../'
		], #include_dirs		
	}, #target_defaults
}