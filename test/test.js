#!/usr/bin/env node

var assert = require( 'assert' )
  , cp = require( 'child_process' )
  , events = require( 'events' )
  , path = require( 'path' )
  , fs = require( 'graceful-fs' )
  , emitter = new events.EventEmitter
  , util = require( 'util' )
  , gr = require( 'gyp-reader' );

assert( typeof cp !== 'undefined' );

emitter.on( 'run', function( defPath ) {
	console.log( 'run: ', defPath );
});

emitter.on( 'build', function( defPath ) {
	console.log( 'build: ', defPath );
});

emitter.on( 'generate', function(defPath) {
	console.log( 'generate: ', defPath );
});

emitter.on( 'run', function(target) {
	cp.spawn( './build/Default/' + target, [], {
		stdio: 'inherit'
	})
	.on( 'close', function( code ) {
		if (!code) {
			console.log( 'test passed' );
		}
		else {
			console.log( 'failed with exit code: ', code );
		}
	});
});

emitter.on( 'build', function( defFile ) {
	var defName = path.basename( defFile, '.gyp' );
	
	cp.spawn( 'xcodebuild', [
			"-project",
			defName + '.xcodeproj'
		], {
		cwd: path.join( __dirname, 'build' )
	} )
	.on( 'close', function( code ) {
		if (!code) {
			gr( defFile, function( err, data ) {
				data.targets.forEach( function( target ) {
					emitter.emit( 'run', target.target_name );
				} );
			} );
		}
	} );

} );

emitter.on( 'generate', function( defFile ) {
	cp.spawn( 'gyp', [
		defFile,
		'--depth==0', 
		'--generator-output=build'
	] )
	.on( 'close', function( code ) {
		if (!code) {
			emitter.emit( 'build', defFile );
		}
	} );
} );

emitter.on( 'traverse', function( testDir ) {
	fs.readdir( testDir, function( err, files ) {
		files.forEach( function( file ) {
			if (path.extname(file) == '.gyp') {
				emitter.emit( 'generate', file ); 
			}
		} );	
	} );
}); 

emitter.emit( 'traverse', __dirname );