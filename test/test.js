#!/usr/bin/env node

var assert = require( 'assert' )
  , cp = require( 'child_process' )
  , path = require( 'path' )
  , Expector = require( 'expector' ).Expector
  , test = require( 'tape' )
  , thisPath = path.dirname(__filename)
  , plankScript = path.join( thisPath, '../bin/test.js' );

process.chdir( thisPath ); 

test( 'test build', function(t) {
	var controller = makeExpector(t);
	controller.expect( 'hello test\n' );

	cp
	.fork( plankScript )
	.on( 'exit', function(code) {
		t.assert( !code );
		runBuild( './build/Test/test', controller );  
	});
});

test( 'release build', function(t) {
	var controller = makeExpector(t);
	controller.expect( 'hello release\n' );

	cp
	.fork( 
		  plankScript
		, ['-r'] )
	.on( 'exit', function(code) {
		t.assert( !code );
		runBuild( './build/Release/test', controller ); 
	});
});

test( 'debug build', function(t) {
	var controller = makeExpector(t);
	controller.expect( 'hello debug\n' );

	cp
	.fork( 
		  plankScript
		, ['-d'] )
	.on( 'exit', function(code) {
		t.assert( !code );
 	 	runBuild( './build/Debug/test', controller );
	});
});

function makeExpector(tape) {
	var controller = new Expector(tape)
	  , tmpCheck = controller.check; 

	controller.check = function() {
		tmpCheck();
		tape.end();
	};

	return controller;
}

function runBuild( path, controller ) {
	cp.execFile( path, function(err, stdout, stderr) {
		if(err) throw err;
		controller.emit( stdout );
		controller.check();
	} );
}
