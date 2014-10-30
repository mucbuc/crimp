#!/usr/bin/env node

var cp = require( 'child_process' )
  , base = require( './.base.js' )
  , config = require( '../config' )
  , build = cp.fork( 'build_target' );

build.on( 'close', function() {
	testBuild( base.makeEmitter() )
} );

function testBuild(emitter)
{
	var test = new base.Processor( config.run, emitter );
	console.log( 'test build' );
	emitter.emit( 'execute' );
}
