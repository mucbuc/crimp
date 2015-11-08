
var assert = require( 'assert' )
  , path = require( 'path' )
  , cp = require( 'child_process' )
  , copy = require( 'fs-extra' ).copy
  , fs = require( 'graceful-fs' )
  , Printer = require( './printer' )
  , rmrf = require( 'rmrf' )
  , gff = require( './ggf.js' );

assert( typeof copy === 'function' );

function Base(program) {

  this.clean = function(o, cb) {
    console.log( 'clean', o.output );
    rmrf( o.output );
    cb(); 
  };

  this.readSuites = function(suite, cb) {
    fs.readFile( suite, function(err, data) {
      if (err) throw err; 
      cb( JSON.parse( data.toString() ).tests );
    });
  }; 

  this.generate = function( o, cb ) {

    assert( o.hasOwnProperty( 'output' ) );
    assert( o.hasOwnProperty( 'testDir' ) );
    assert( o.hasOwnProperty( 'defFile' ) );

    var include = program.gcc ? 'cpp11-gcc.gypi' : 'cpp11.gypi'
      , args = [
        path.join( o.output, o.defFile ),
        '--depth=' + (program.gcc ? './' : '.'),
        '--generator-output=' + o.output,
        '--include=' + path.join( __dirname, '../def', include )
      ];

    if (program.gcc) {
      args.push( '--format=make' );
    }

    if (program.debug) {
      args.push( '--build=Debug' );  
    }
    else if (program.release) {
      args.push( '--build=Release' );
    }

    cp.spawn( 
      'gyp', 
      args, {
        stdio: 'inherit',
        cwd: o.testDir
      })
    .on( 'close', function( code ) {
      cb( code, o.output );
    });
  };

  this.makePathIfNone = makePathIfNone;

  this.traverse = function( dir, cb ) {
    fs.readdir( dir, function( err, files ) {
      var found = false;
      if (err) throw err;
      files.forEach( function( file, index, array ) {
        if (path.extname(file) == '.json') {
          found = true;
          cb( file ); 
        }
        else if (!found && index == array.length - 1) {
          throw 'no json file found'; 
        }
      } );    
    } );
  };
 
  this.run = function( o, cb ) {
    var execPath;
    o.output = path.join( o.testDir, o.output );
    if (program.gcc) {
      o.testDir = path.join( o.testDir, 'out' );
      execPath = path.join( o.output, 'out/Test', o.target );
    }
    else if (program.debug) {
      execPath = path.join( o.output, 'Debug', o.target );
    }
    else if (program.release) {
      execPath = path.join( o.output, 'Release', o.target );
    }
    else {
      execPath = path.join( o.output, 'Test', o.target );
    }

    cp.spawn( 
      execPath, 
      [ 'http://localhost:3000' ], {
      stdio: 'pipe'
    })
    .on( 'error', function( error ) {
      console.log( error );
    })
    .on( 'close', function( code ) {
      cb( code );
      //server.kill();
    })
    .stdout.on( 'data', function( data ) {
      Printer.cursor.blue();
      process.stdout.write( o.defFile + ': ' ); 
      Printer.cursor.reset();
      console.log( data.toString() );
    });
  };
  
  function makePathIfNone( path, cb ) {
    fs.exists(path, function(exists) {
      if (exists) 
        cb();
      else 
        fs.mkdir( path, [], cb ); 
    });
  }
}

module.exports = Base;
