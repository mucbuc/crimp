#!/usr/bin/env node

var fs = require( 'fs' )
  , path = require( 'path' )
  , util = require( 'util' )
  , assert = require( 'assert' )
  , Printer = require( './printer' );

function defineGYP(pathJSON, pathGYP, cb) {

	assert( fs.existsSync( pathJSON ), "project json missing" ); 

	Printer.begin( 'define' ); 

	fs.readFile( pathJSON, function(err, data) {
		var content
		  , gyp;

		if (err) throw err;
		content = JSON.parse( data.toString() );
		gyp = {
			target_defaults: {
				target_name: 'test',
				type: 'executable',
				sources: content.sources
			}
		};

		fs.writeFile( pathGYP, JSON.stringify( gyp, null, 2 ), null, function() {
			Printer.finishGreen( 'define' );
			cb();
		} ); 
	});
}

module.exports = defineGYP;
