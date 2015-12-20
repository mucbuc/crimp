#!/usr/bin/env node

var assert = require( 'assert' )
  , program = require( 'commander' )
  , buildProject = require( './bin/controller.js' )
  , path = require( 'path' )
  , rmrf = require( 'rmrf' )
  , cp = require( 'child_process' )
  , fs = require( 'fs' )
  , traverse = require( 'traverjs' );

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
  .option( '-l , --linkOpengl', 'link opengl libs' )
  .parse( process.argv );

var options = { 
      buildDir: 'build',
      targetName: 'test',
      testDir: '.',
      pathJSON: './test.json'
  };
  
if (program.release) {
  options.release = true;
}
else if (program.debug) {
  options.debug = true;
} 
else {
  options.test = true;
  options.execute = true;
}

if (program.output) {
  options.buildDir = program.output;
}

if (program.gcc) {
  options.gcc = true;
}

if (program.execute) {
  options.execute = true;
}

if (program.ide) {
  options.ide = program.ide;
}

if (program.path) {
  options.pathJSON = path.basename( program.path );
  options.testDir = path.dirname( program.path );
}
else if (program.suite) {
  options.testDir = path.dirname( program.suite );
  program.suite = path.basename( program.suite );
}

process.chdir( options.testDir );

if (program.clean) {
  rmrf( options.buildDir ); 
}

if (program.linkOpengl) {
  options.linkOpengl = program.linkOpengl;
}

if (program.suite) {
  fs.readFile( program.suite, function(err, data) {
    if (err) throw err; 
    
    traverse( JSON.parse( data.toString() ).tests, function( pathJSON, next ) {
       options.pathJSON = pathJSON; 
       buildProject( options, next );
    } )
    .then( function() {
      
    });
  });
}
else {
  buildProject( options );
}