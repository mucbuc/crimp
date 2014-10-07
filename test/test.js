#!/usr/bin/env node

var assert = require( 'assert' )
  , cp = require( 'child_process' )
  , events = require( 'events' )
  , path = require( 'path' )
  , emitter = new events.EventEmitter;

assert( typeof cp !== 'undefined' );

emitter.on( 'run', function() {
	console.log( 'run' );
});

emitter.on( 'build', function() {
	console.log( 'build' );
});

emitter.on( 'generate', function() {
	console.log( 'generate' );
});

emitter.on( 'run', function() {
	var cwd = path.join( __dirname, 'build', 'Default' );
	cp.spawn( 'test', [], {
		cwd: cwd, 
		stdio: 'inherit'
	})
	.on( 'close', function( code ) {
		if (!code) {
			console.log( 'test passed' );
		}
	} ); 
});

emitter.on( 'build', function() {
	cp.spawn( 'xcodebuild', [], {
		cwd: __dirname,
		stdio:'inherit'
	} )
	.on( 'close', function( code ) {
		if (!code) {
			emitter.emit( 'run' );
		}
	} );
} );

emitter.on( 'generate', function() {
	cp.spawn( 'gyp', [ 
		'--depth==0', 
		'test/test.gyp' 
	], { 
		stdio:'inherit' 
	} )
	.on( 'close', function( code ) {
		if (!code) {
			emitter.emit( 'build' );
		}
	} );
} );

emitter.emit( 'generate' );