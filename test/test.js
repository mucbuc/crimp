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
  controller.expect( 0 );

  fs.unlink( resultPath, function(err) {
    tryOpen();
    crimp([ '-p', path.join( __dirname, 'check_assert.json' ) ], controller, tryOpen );
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
  
  var controller = new Expector(t);
  
  controller.expect( 0 );

  crimp([ '-d', '-p', path.join( __dirname, 'test-data.json' ) ], controller );
}); 

test( 'test build', function(t) {
  var controller = new Expector(t); 

  controller.expect( 'hello test\n' );
  controller.expect( 0 );

  crimp([ '-p', path.join( __dirname, 'test.json' ) ], controller );
});

test( 'release build', function(t) {
  var controller = new Expector(t);

  controller.expect( 'hello release\n' );
  controller.expect( 0 );
  
  crimp([ '-r', '-e', '-p', path.join( __dirname, 'test.json' ) ], controller );
});

test( 'debug build', function(t) {
  var controller = new Expector(t);

  controller.expect( 'hello debug\n' );
  controller.expect( 0 );

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

function crimp(args, controller, cb) {
  var child = cp
  .spawn( path.join( __dirname, '../crimp.js'), 
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
