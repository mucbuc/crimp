#!/usr/bin/env node

var assert = require( 'assert' )
  , cp = require( 'child_process' )
  , path = require( 'path' )
  , Expector = require( 'expector' ).Expector
  , test = require( 'tape' )
  , thisPath = path.dirname(__filename)
  , buildProject = require( '../bin/controller.js' )
  , fs = require( 'fs' );

process.chdir( thisPath );

test( 'data include', (t) => {
 
  var controller = new Expector(t);
  
  controller.expect( 0 );

  crimp([ '-d', 'test-data.json' ], controller );
}); 

test.skip( 'test build', (t) => {
  var controller = new Expector(t); 

  controller
  .expect( 'hello test\n' )
  .expect( 0 );

  crimp([ 'test.json' ], controller );
});

test( 'test gcc build', (t) => {
  var controller = new Expector(t);

  controller
  .expect( 'hello test\n' )
  .expect( 0 ); 
  crimp([ '-g', 'test.json' ], controller );
});

test( 'release gcc build', (t) => {
  
  var controller = new Expector(t);

  controller
  .expect( 'hello release\n' )
  .expect( 0 ); 
  crimp([ '-g', '-r', '-e', 'test.json' ], controller );
});

test( 'debug gcc build', (t) => {
  var controller = new Expector(t);
  
  controller
  .expect( 'hello debug\n' )
  .expect( 0 ); 

  crimp([ '-g', '-d', '-e', 'test.json' ], controller );
});

test.skip( 'release build', (t) => {
  var controller = new Expector(t);

  controller
  .expect( 'hello release\n' )
  .expect( 0 );
  
  crimp([ '-r', '-e', 'test.json' ], controller );
});

test.skip( 'debug build', (t) => {
  var controller = new Expector(t);

  controller
  .expect( 'hello debug\n' )
  .expect( 0 );

  crimp([ '-d', '-e', 'test.json' ], controller );
});

function crimp(args, controller, cb) {
  var child = cp
  .fork( path.join( __dirname, '..', 'crimp.js'), 
          args, 
          { silent: true } )
  .on( 'exit', (code) => {
    
    if (typeof cb !== 'undefined') {
      cb();
    }
    controller.emit( code );
    controller.check(); 
  });
  child.stdout.on( 'data', (data) => {
    controller.emit( data.toString() ); 
  });

  return child;
}
