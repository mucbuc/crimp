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
        'include_dirs': [
			'crimp/src/',
		],	
    }
}