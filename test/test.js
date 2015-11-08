#!/usr/bin/env node

var assert = require( 'assert' )
  , cp = require( 'child_process' )
  , path = require( 'path' )
  , Expector = require( 'expector' ).Expector
  , test = require( 'tape' )
  , thisPath = path.dirname(__filename)
  , define = require( '../bin/definer.js' )
  , generate = require( '../bin/generator.js' )
  , build = require( '../bin/builder.js' )
  , buildProject = require( '../bin/controller.js' );

process.chdir( thisPath ); 

test( 'test controller', function(t) {
  var expector = new Expector(t);
  expector.expect( 'done' );
  buildProject( './test.json', function() {
    expector.emit( 'done' );
    expector.check(); 
  });
});

test( 'test definer', function(t) {
  var controller = new Expector(t);
  controller.expect( '{"sources":["../src/main.cpp"]}' );
  define( './test.json' )
  .then( function(product) {
    controller.emit( JSON.stringify(product) ); 
    controller.check();
  });
});

test( 'test build', function(t) {
  var controller = new Expector(t);
  controller.expect( 'hello test\n' );

  buildProject( 'test.json', function(code) {
    t.assert( !code );
    runBuild( './build/build/Test/test', controller );  
  });
});

/*
test( 'release build', function(t) {
  var controller = new Expector(t);
  controller.expect( 'hello release\n' );

  runPlank( ['-r'], function(code) {
    t.assert( !code );
    runBuild( './build/build/Release/test', controller ); 
  });
});


test( 'debug build', function(t) {
  var controller = new Expector(t);
  controller.expect( 'hello debug\n' );

  runPlank( ['-d'], function(code) {
    t.assert( !code );
    runBuild( './build/build/Debug/test', controller );
  });
});
*/

function runBuild( path, controller ) {
  cp.execFile( path, function(err, stdout, stderr) {
    console.log( err );
    if(err) {
      console.log( path, process.cwd() );
      throw err;
    }
    controller.emit( stdout );
    controller.check();
  } );
}
