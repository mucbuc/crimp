#!/usr/bin/env node

var cp = require( 'child_process' )
  , base = require( './.base.js' )
  , config = require( '../config.json' )
  , generate = cp.fork( 'generate_project' );

generate.on( 'close', function() {
	buildTarget( base.makeEmitter() )
} );

function buildTarget(emitter)
{
	var build = new base.Processor( config.build, emitter );
	console.log( 'build target' );
	emitter.emit( 'execute' );
}
