
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

  this.define = function(def, out, cb) {
    var buildDir = path.dirname(out);
    console.log( 'define', buildDir );
    makePathIfNone(buildDir, function() {
      gff( def, function(product) {
        var gyp = {
            target_defaults: {
              target_name: 'test',
              type: 'executable',
              sources: product.sources,
              include_dirs: [ '../' ]
            }
          };

        fs.writeFile( out, JSON.stringify( gyp, null, 2 ), null, function() {
          Printer.finishGreen( 'define' );
          cb();
        } ); 
      });
    }); 
  };

  this.generate = function( o, cb ) {

    assert( o.hasOwnProperty( 'output' ) );
    assert( o.hasOwnProperty( 'testDir' ) );
    assert( o.hasOwnProperty( 'defFile' ) );

    makePathIfNone(o.output, function() {

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

      console.log( args );

      cp.spawn( 
        'gyp', 
        args, {
          stdio: 'inherit',
          cwd: o.testDir
        })
      .on( 'close', function( code ) {
        cb( code, o.output );
      });
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

  this.build = function( o, cb ) {
    
    readTargetName( o.defFile, o.output, function( targetName ) { 

      o.output = path.join(o.output, 'build');
      var child = null; 
      if (program.gcc) {
        child = cp.spawn(
          'make',
          [ '-j'],
          {
            stdio: 'inherit',
            cwd: o.output
          }); 
      }
      else {

        var projectPath = path.join( o.output, targetName + '.xcodeproj' )
          , args = [
            "-project",
            targetName + '.xcodeproj'
          ];  

        if (program.IDE) {
          console.log( 'open', projectPath );
          cp.spawn( 'open', [ projectPath ] );
        }
        
        console.log( args, o.output, process.cwd() ); 

        child = cp.spawn( 
          'xcodebuild', 
          args, {
            cwd: path.join( o.testDir, o.output ),
            stdio: 'inherit'
          } );
      }
      assert(child); 
      child.on( 'close', function( code ) {
        o['target'] = targetName;
        o['exitCode'] = code;
        cb( o ); 
      } );
    } );

    function readTargetName(defFile, testDir, cb) {
      var defPath = path.join( testDir, defFile );
      fs.readFile( defPath, function( err, data ) {
        if (err) {
          Printer.cursor.red();
          process.stdout.write( defFile + ': ' );
          Printer.cursor.reset();
          console.log( err );
        }
        else {
          var matches = data.toString().match( /'target_name'\s*:\s*'(.*)'/ )
          if (!matches) {
            matches = data.toString().match( /"target_name"\s*:\s*"(.*)"/ )
          }
          if (matches) {
            cb( matches[1] );
          }
        }
      } ); 
    }
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
