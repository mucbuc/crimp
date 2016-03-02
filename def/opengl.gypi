{
	'target_defaults': {
		'conditions': [
			[ 
				'OS=="mac"', {
					'link_settings': {
				        'libraries': [
				            'AppKit.framework',
				            'Foundation.framework',
				            'OpenGL.framework',
				            'QuartzCore.framework',
				        ]
				    }
				}
			], [
				'OS=="linux"', {
					'libraries': [
						'-lGL',
						'-lGLU'
					]
        		}
        	], [
        		'OS=="win"', {
					'libraries': [
						'-lopengl32.lib',
						'-lglu32.lib'
					]
				}
			]
		]
	}
}