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

test( 'asserter', function(t) {
   var controller = new Expector(t)
    , options = { 
        buildDir: 'build',
        targetName: 'test',
        testDir: '.',
        pathJSON: './check_assert.json'
      }
    , resultPath = './build/result.json';

  controller.expect( 'not exits' ); 
  controller.expect( 'exits' ); 

  fs.unlink( resultPath, function(err) {

    tryOpen();

    buildProject( options, function(code) {
      t.assert( !code );
      cp.spawn( './build/build/Test/test', [], {stdio: 'inherit' })
      .on( "exit", function() {
        tryOpen();
        controller.check();
      } );
    });
  } );

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
  var controller = new Expector(t); 

  controller.expect( 'hello test\n' );

  crimp([ '-p', path.join( __dirname, 'test.json' ) ], controller );
});

test( 'release build', function(t) {
  var controller = new Expector(t);

  controller.expect( 'hello release\n' );
  
  crimp([ '-r', '-e', '-p', path.join( __dirname, 'test.json' ) ], controller );
});

test.only( 'debug build', function(t) {
  var controller = new Expector(t);

  controller.expect( 'hello debug\n' );

  crimp([ '-d', '-e', '-p', path.join( __dirname, 'test.json' ) ], controller );
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

function crimp(args, controller) {
  var child = cp
  .spawn( path.join( __dirname, '../crimp.js'), 
          args, 
          { stdio: 'pipe' } )
  .on( 'exit', function() {
    controller.check(); 
  });
  child.stdout.on( 'data', function(data) {
    controller.emit( data ); 
  });
}
