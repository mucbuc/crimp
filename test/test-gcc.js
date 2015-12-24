#!/usr/bin/env node

var assert = require( 'assert' )
  , cp = require( 'child_process' )
  , path = require( 'path' )
  , Expector = require( 'expector' ).Expector
  , test = require( 'tape' )
  , thisPath = path.dirname(__filename)
  , define = require( '../bin/definer.js' )
  , buildProject = require( '../bin/controller.js' );

process.chdir( thisPath ); 

test( 'test controller', function(t) {
  var expector = new Expector(t)
    , options = { 
        buildDir: 'build',
        targetName: 'test',
        testDir: '.',
        pathJSON: './test.json',
        gcc: 'true'
    };

  expector.expect( 'done' );
  buildProject( options, function() {
    expector.emit( 'done' );
    expector.check(); 
  });
});

test( 'test definer', function(t) {
  var controller = new Expector(t);
  controller.expect( '["../src/main.cpp"]' );
  define( './test.json' )
  .then( function(product) {
    t.assert( product.hasOwnProperty("sources" ) ); 
    controller.emit( JSON.stringify(product.sources) ); 
    controller.check();
  });
});

test( 'test build', function(t) {
  var controller = new Expector(t)
    , options = { 
        buildDir: 'build',
        targetName: 'test',
        testDir: '.',
        pathJSON: './test.json',
        gcc: 'true'
    };

  controller.expect( 'hello test\n' );

  buildProject( options, function(code) {
    t.assert( !code );
    runBuild( './build/out/Test/test', controller );  
  });
});

test( 'release build', function(t) {
  
  var controller = new Expector(t)
    , options = { 
        buildDir: 'build',
        targetName: 'test',
        testDir: '.',
        pathJSON: './test.json',
        release: 'true',
        gcc: 'true'
    };

  controller.expect( 'hello release\n' );

  buildProject( options, function(code) {
    t.assert( !code );
    runBuild( './build/out/Release/test', controller ); 
  });
});

test( 'debug build', function(t) {
  var controller = new Expector(t)
    , options = { 
        buildDir: 'build',
        targetName: 'test',
        testDir: '.',
        pathJSON: './test.json',
        debug: 'true',
        gcc: 'true'
    };
  controller.expect( 'hello debug\n' );

  buildProject( options, function(code) {
    t.assert( !code );
    runBuild( './build/out/Debug/test', controller );
  });
});

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
