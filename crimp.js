#!/usr/bin/env node

var assert = require( 'assert' )
  , program = require( 'commander' )
  , buildProject = require( './bin/controller.js' )
  , path = require( 'path' )
  , fs = require( 'fs.extra' )
  , traverse = require( 'traverjs' )
  , Context = require( './bin/context' )
  , Printer = require( './bin/printer' )
  , version = require( './package.json' ).version

program
  .version( version )
  .option( '-o, --output [path]', 'build output (default: build)' )
  .option( '-p, --path [path]', 'test path (default .)' )
  .option( '-s, --suite [path]', 'suite json' )
  .option( '-t, --test', 'test build (default)' )
  .option( '-d, --debug', 'target debug' )
  .option( '-r, --release', 'target release' )
  .option( '-c, --clean', 'clean build' )
  .option( '-g, --gcc', 'use gcc compiler' )
  .option( '-e, --execute', 'execute product' )
  .option( '-i, --ide', 'open project in ide' )
  //.option( '-v, --verbose', 'output everything' )
  //.option( '-q, --sequence', 'run tests in sequence')
  .parse( process.argv );

program.verbose = true;
program.sequence = true;

if (program.suite) {

  var dirname = path.dirname( program.suite );
  Printer.begin( 'total', program.suite );  
  fs.readFile( program.suite, function(err, data) {
    var tests; 
    if (err) throw err;
    tests = JSON.parse( data.toString() ).tests;
    
    if (program.sequence) {
      traverse( tests, function( pathJSON, next ) { 
        crimpIt( path.join( dirname, pathJSON ), next );
      } )
      .then( function() {
        Printer.finishGreen( 'total', program.suite );
      });
    }
    else {
      process.on( 'exit', function() {
        Printer.finishGreen( 'total', program.suite );
      });
      tests.forEach( function( pathJSON ) {
        crimpIt( path.join( dirname, pathJSON ) );
      });
    }
  });
}
else {
  crimpIt( program.path );
}

function crimpIt(pathJSON, cb) {

  var context = new Context( program, pathJSON ); 

  if (program.clean) {
    fs.rmrf( path.join( context.testDir, context.tempDir ), function(err) {
      if (err) throw err;
      buildProject( context, cb );
    });
  }
  else {
    buildProject( context, cb );
  }
}


