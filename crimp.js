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
  , assertCount = 0; 

program
  .version( version )
  .option( '-o, --output [path]', 'build output (default: build)' )
  .option( '-t, --test', 'test build (default)' )
  .option( '-d, --debug', 'target debug' )
  .option( '-r, --release', 'target release' )
  .option( '-c, --clean', 'clean build' )
  .option( '-g, --gcc', 'use gcc compiler' )
  .option( '-e, --execute', 'execute product' )
  .option( '-i, --ide', 'open project in ide' )
  .option( '-x, --xargs []', 'pass on arguments' )
  //.option( '-v, --verbose', 'output everything' )
  //.option( '-q, --sequence', 'run tests in sequence')
  .action( function() {

    var args = [];
    for (var i = 0; i < arguments.length - 1; ++i) {
      args.push( arguments[i] );
    }

    program.verbose = true;
    program.sequence = true;
    
    Printer.begin( 'total', 'test run' );
    process.on( 'exit', function() {
      Printer.finishGreen( 'total' );
      console.log( 'assertions passed: ', assertCount ); 
    });
    
    traverse( args, function( arg, next) {
      var pathJson = arg 
        , dirname = path.dirname( pathJson );

      fs.readFile( pathJson, function(err, data) {
        var tests; 
        if (err) throw err;
        // this readFile and JSON.parse seems wasteful and redundant
        tests = JSON.parse( data.toString() ).tests;
        if (typeof tests !== 'undefined') {
          traverse( tests, function( pathJSON, next ) { 
            crimpIt( path.join( dirname, pathJSON ), makeAccumulator(next) );
          } );
        }
        else {
          crimpIt( pathJson, makeAccumulator(next) ); 
        }

        function makeAccumulator(next) {
          return function(result) {
            if (typeof result === 'number' ) {
              assertCount += result; 
            }
            next();
          };
        }
      });
    });
  })
  .parse( process.argv );

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


