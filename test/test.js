#!/usr/bin/env node

var assert = require( 'assert' )
  , cp = require( 'child_process' )
  , path = require( 'path' )
  , Expector = require( 'expector' ).Expector
  , test = require( 'tape' )
  , thisPath = path.dirname(__filename)
  , buildProject = require( '../bin/controller.js' );

process.chdir( thisPath );

test( 'data include', function(t) {
  
  var controller = new Expector(t)
    , options = { 
        buildDir: 'build',
        targetName: 'test',
        testDir: '.',
        pathJSON: './test-data.json',
        debug: 'true'
    };
  
  controller.expect( 'built' ); 
  buildProject( options, function() {
    controller.emit( 'built' ).check();
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
    controller.emit( stdout ).check();
  } );
}
