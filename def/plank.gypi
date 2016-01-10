{	
	'includes':[
		'mac-targets.gypi'
	],
    'target_defaults': {
    	'default_configuration': 'Test',
		'type': 'executable',
		'configurations':{
	       	'Release': {
	         	'defines': [
	           		'NDEBUG',
	        	],
	       	},
	       	'Debug': {
	       		'defines': [
	       			'TARGET_DEBUG=1'
	       		],
	       	},
	       	'Test': {
	       		'defines': [
	       			'TARGET_TEST=1'
	       		],
	       	}	
	    },
        'sources': [
			'../src/archiver.cpp',
			'../src/archiver.h',
			'../src/asserter.cpp',
			'../src/asserter.h',
			'../src/asserter.hxx',
			'../src/test.h'
        ],
        'include_dirs': [
			'crimp/src/',
		],	
    }
}