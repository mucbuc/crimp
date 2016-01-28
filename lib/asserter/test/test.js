#!/usr/bin/env node

var test = require( 'tape' )
  , fs = require( 'fs' )
  , cp = require( 'child_process' )
  , Expector = require( 'expector' ).SeqExpector;

test( 'asserter', function(t) {
  var controller = new Expector(t)
   ,  resultPath = './tmp/result.json';

  controller
  .expect( 'not exits' )
  .expect( 'exits' )
  .expect( 0 );

  fs.unlink( resultPath, function(err) {
    tryOpen();
    crimp([ '-p', 'check_assert.json' ], controller, tryOpen );
  } );
  
  function crimp(args, controller, cb) {
    var child = cp
    .spawn( 'crimp', 
            args, 
            { stdio: 'pipe' } )
    .on( 'exit', function(code) {
      
      if (typeof cb !== 'undefined') {
        cb();
      }
      controller.emit( code );
      controller.check(); 
    });
    child.stdout.on( 'data', function(data) {
      controller.emit( data ); 
    });

    return child;
  }

  function tryOpen() {
    try {
      fs.statSync( resultPath );
      controller.emit( "exits" );   
    }
    catch(err) {
      controller.emit( "not exits" );
    }
  } 

});
