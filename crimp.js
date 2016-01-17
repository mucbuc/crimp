#!/usr/bin/env node

var assert = require( 'assert' )
  , program = require( 'commander' )
  , buildProject = require( './bin/controller.js' )
  , path = require( 'path' )
  , rmrf = require( 'rmrf' )
  , fs = require( 'fs' )
  , traverse = require( 'traverjs' )
  , Context = require( './bin/context' );

program
  .version( '0.0.1' )
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
  .option( '-v, --verbose', 'output everything' )
  .parse( process.argv );

if (program.suite) {

  var dirname = path.dirname( program.suite );

  fs.readFile( program.suite, function(err, data) {
    if (err) throw err; 
    
    traverse( JSON.parse( data.toString() ).tests, function( pathJSON, next ) {
      crimpIt( path.join( dirname, pathJSON ), next );
    });
  });
}
else {
  crimpIt( program.path );
}

function crimpIt(pathJSON, cb) {

  var context = new Context( program ); 

  context.pathJSON = path.basename( pathJSON );
  context.testDir = path.join( process.cwd(), path.dirname( pathJSON ) );

  if (program.clean) {
    rmrf( path.join( context.testDir, context.tempDir ) ); 
  }

  buildProject( context, cb );
}


