#!/usr/bin/env node

var path = require( 'path' )
  , util = require( 'util' )
  , test = require( 'tape' )
  , thisPath = path.dirname(__filename);

process.chdir( thisPath );

test( 'ggf recursion', function(t) {
	var ggf = require( '../bin/ggf.js' )
	  , expected = { 
		"sources": [
			'../lib/sublib/src/subsrc.h', 
			'../lib/sublib/src/subsrc.cpp', 
			'../lib/sublib2/src/subsrc.cpp'
		]
	};		
	ggf( './test-import.json' ).then( function(gyp) {
		t.deepEqual( gyp, expected ); 
		t.end();
	} );
});
