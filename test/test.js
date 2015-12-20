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

test( 'data prep', function(t) {
  var ggf = require( '../bin/ggf.js' );
  ggf( './test-data.json' )
  .then( function(gyp) {
    t.assert( gyp.hasOwnProperty('data') );
    t.assert( gyp.data.length );
    t.end(); 
  });
});

test( 'ggf recursion', function(t) {
  var ggf = require( '../bin/ggf.js' )
    , expected = [
      '../lib/sublib/src/subsrc.h', 
      '../lib/sublib/src/subsrc.cpp', 
      '../lib/sublib2/src/subsrc.cpp'
    ];    
  ggf( './test-import.json' ).then( function(gyp) {
    t.assert( gyp.hasOwnProperty( 'sources' ) );
    t.deepEqual( gyp.sources, expected ); 
    t.end();
  } );
});

test( 'test controller', function(t) {
  var expector = new Expector(t)
    , options = { 
        buildDir: 'build',
        targetName: 'test',
        testDir: '.',
        pathJSON: './test.json'
    };

  expector.expect( 'done' );
  buildProject( options, function() {
    expector.emit( 'done' );
    expector.check(); 
  });
});

test( 'test definer', function(t) {
  var controller = new Expector(t);
  controller.expect( '{"sources":["../src/main.cpp"]}' );
  define( './test.json', '.' )
  .then( function(product) {
    controller.emit( JSON.stringify(product) ); 
    controller.check();
  });
});

test( 'test build', function(t) {
  var controller = new Expector(t)
    , options = { 
        buildDir: 'build',
        targetName: 'test',
        testDir: '.',
        pathJSON: './test.json'
    };

  controller.expect( 'hello test\n' );

  buildProject( options, function(code) {
    t.assert( !code );
    runBuild( './build/build/Test/test', controller );  
  });
});

test( 'release build', function(t) {
  var controller = new Expector(t)
    , options = { 
        buildDir: 'build',
        targetName: 'test',
        testDir: '.',
        pathJSON: './test.json',
        release: 'true'
    };

  controller.expect( 'hello release\n' );

  buildProject( options, function(code) {
    t.assert( !code );
    runBuild( './build/build/Release/test', controller ); 
  });
});

test( 'debug build', function(t) {
  var controller = new Expector(t)
    , options = { 
        buildDir: 'build',
        targetName: 'test',
        testDir: '.',
        pathJSON: './test.json',
        debug: 'true'
    };
  controller.expect( 'hello debug\n' );

  buildProject( options, function(code) {
    t.assert( !code );
    runBuild( './build/build/Debug/test', controller );
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
