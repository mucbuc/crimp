#!/usr/bin/env node

var base = require( './.base.js' )
  , config = require( '../config.json' );

generateProject( base.makeEmitter() ); 

function generateProject( emitter ) 
{
	var p = new base.Processor( config.generate , emitter );
	console.log( 'generate project' );
	emitter.emit( 'execute' );
}