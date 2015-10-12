#!/usr/bin/env node

var ggf = require( '../bin/ggf.js' )
  , util = require( 'util' )
  , test = require( 'tape' );

test( 'ggf recursion', function(t) {
	var expected = { 
		"sources": [
			'src/main.cpp', 
			'src/subsrc.h', 
			'src/subsrc.cpp', 
			'src/sub2src.cpp'
		]
	};		
	ggf( './test.json', function(gyp) {
		t.deepEqual( gyp, expected ); 
		t.end();
	} );
});
