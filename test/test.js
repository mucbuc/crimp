#!/usr/bin/env node

var assert = require( 'assert' )
  , cp = require( 'child_process' )
  , path = require( 'path' )
  , Expector = require( 'expector' ).Expector
  , test = require( 'tape' );

test( 'test build', function(t) {
	var controller = new Expector();

	t.plan( 1 ); 	

	controller.expect( 'built' ); 
	controller.expect( 'hello test\n' );

	cp
	.fork( path.join( __dirname, 'plank/bin/test.js' ) )
	.on( 'exit', function() {
		controller.emit( 'built' );
		cp.execFile( path.join( __dirname, '/build/Test/test' ), function(err, stdout, stderr) {
			if(err) throw err;
			controller.emit( stdout );
			controller.check();
			t.pass();
		} ); 
	});
});

test( 'release build', function(t) {
	var controller = new Expector();

	t.plan( 1 ); 	
	controller.expect( 'built' ); 
	controller.expect( 'hello release\n' );

	cp
	.fork( 
		  path.join( __dirname, 'plank/bin/test.js' )
		, ['-r'] )
	.on( 'exit', function() {
		controller.emit( 'built' );
		cp.execFile( path.join( __dirname, '/build/Release/test' ), function(err, stdout, stderr) {
			if(err) throw err;
			controller.emit( stdout );
			controller.check();
			t.pass();
		} ); 
	});

});

test( 'debug build', function(t) {
	var controller = new Expector();

	t.plan( 1 ); 	
	controller.expect( 'built' ); 
	controller.expect( 'hello debug\n' );

	cp
	.fork( 
		  path.join( __dirname, 'plank/bin/test.js' )
		, ['-d'] )
	.on( 'exit', function() {
		controller.emit( 'built' );
		cp.execFile( path.join( __dirname, '/build/Debug/test' ), function(err, stdout, stderr) {
			if(err) throw err;
			controller.emit( stdout );
			controller.check();
			t.pass();
		} ); 
	});

});