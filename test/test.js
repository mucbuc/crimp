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

test( 'data include', function(t) {
  
  var controller = new Expector(t);
  
  controller.expect( 0 );

  crimp([ '-d', '-p', 'test-data.json' ], controller );
}); 

test( 'test build', function(t) {
  var controller = new Expector(t); 

  controller
  .expect( 'hello test\n' )
  .expect( 0 );

  crimp([ '-p', 'test.json' ], controller );
});

test( 'test gcc build', function(t) {
  var controller = new Expector(t);

  controller
  .expect( 'hello test\n' )
  .expect( 0 ); 
  crimp([ '-g', '-p', 'test.json' ], controller );
});

test( 'release gcc build', function(t) {
  
  var controller = new Expector(t);

  controller
  .expect( 'hello release\n' )
  .expect( 0 ); 
  crimp([ '-g', '-r', '-e', '-p', 'test.json' ], controller );
});

test( 'debug gcc build', function(t) {
  var controller = new Expector(t);
  
  controller
  .expect( 'hello debug\n' )
  .expect( 0 ); 

  crimp([ '-g', '-d', '-e', '-p', 'test.json' ], controller );
});

test( 'release build', function(t) {
  var controller = new Expector(t);

  controller
  .expect( 'hello release\n' )
  .expect( 0 );
  
  crimp([ '-r', '-e', '-p', 'test.json' ], controller );
});

test( 'debug build', function(t) {
  var controller = new Expector(t);

  controller
  .expect( 'hello debug\n' )
  .expect( 0 );

  crimp([ '-d', '-e', '-p', 'test.json' ], controller );
});

function crimp(args, controller, cb) {
  var child = cp
  .fork( path.join( __dirname, '..', 'crimp.js'), 
          args, 
          { silent: true } )
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
