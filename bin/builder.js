var cp = require( 'child_process' )
  , path = require( 'path' );

function build(options, cb) {
	var pathProject = path.join( options.buildDir, options.buildDir, options.targetName + ".xcodeproj" )
	  , args = ['-project', pathProject ];
	
	cp
	.spawn( 'xcodebuild', args, { stdio: 'inherit' } )
	.on( 'exit', function(code) {
		console.log( 'code', code );
		cb(code);
	});
}

module.exports = build;