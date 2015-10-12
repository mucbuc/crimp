#!/usr/bin/env node

var ggf = require( '../bin/ggf.js' )
  , util = require( 'util' )
  , test = require( 'tape' );

test( 'ggf recursion', function(t) {
	var expected = { 
		"sources": [
			'lib/sublib/src/subsrc.h', 
			'lib/sublib/src/subsrc.cpp', 
			'lib/sublib2/src/sub2src.cpp'
		]
	};		
	ggf( './test-import.json', function(gyp) {
		t.deepEqual( gyp, expected ); 
		t.end();
	} );
});
