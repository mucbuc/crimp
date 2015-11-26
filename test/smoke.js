#!/usr/bin/env node

var test = require( 'tape' )
  , Expector = require( 'expector' ).SeqExpector
  , cp = require( 'child_process' )
  , path = require( 'path' );

test( 'smoke', function(t) {
  var e = new Expector( t ); 
  e.expect( 0 );
  cp
  .fork( path.join( __dirname, '../plank.js'), [ '-p', path.join( __dirname, 'test.json' ) ] )
  .on( 'exit', function(code) {
    e.emit( code );
    e.check();
  });
});