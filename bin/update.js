#!/usr/bin/env node

var assert = require( 'assert' )
  , cp = require( 'child_process' )
  , Reader = require( './Reader' );

Reader.readDependencies().forEach( function( dependency ) {
	var name = Reader.libName( dependency );
	cp.exec( 
		'git subtree pull -P ' + name + ' ' + name + ' master --squash', 
		function(error, stdout, stderr) {
			console.log( stdout );
		} ); 
} ); 
