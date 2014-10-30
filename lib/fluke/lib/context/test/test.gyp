{
	'includes':[
		'../om636.gypi',
		'../plank/def/mac-targets.gypi'
	],#inclues
	'target_defaults': {
		'target_name': 'test', 
		'type': 'executable',
		'sources': [
			'../test/src/components/main.cpp'
		], #sources
		'include_dirs': [
			'../plank/src/',
			'../'
		], #include_dirs		
	}, #target_defaults
}