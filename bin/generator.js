var assert = require( 'assert' )
  , path = require( 'path' )
  , cp = require( 'child_process' )
  , Promise = require( 'promise' );

function generate( options ) {

  assert( options.hasOwnProperty( 'testDir' ) );
  assert( options.hasOwnProperty( 'pathGYP' ) );
  assert( options.hasOwnProperty( 'tempDir' ) );

  return new Promise(function(resolve, reject) {
    var args = [
          options.nameGYP,
          '--generator-output=' + options.buildDir
        ];  

    if (options.gcc) {
      args = args.concat( [
        '--depth=./',
        '--include=' + getPlankGYPI( 'cpp11-gcc.gypi' ),
        '--format=make'
      ]);
    }
    else {
      args = args.concat( [
        '--depth=.',
        '--include=' + getPlankGYPI( 'cpp11.gypi' )
      ]);
    
      if (options.debug) {
        args.push( '--build=Debug' );  
      }
      else if (options.release) {
        args.push( '--build=Release' );
      }
    }

    if (options.opengl) {
      args.push( '--include=' + getPlankGYPI( 'opengl.gypi' ) );
    }

    cp.spawn( 
      'gyp', 
      args, 
      {
        stdio: 'inherit', 
        cwd: path.join( options.testDir, options.tempDir )
      })
    .on( 'exit', function( code ) {
      if (code) 
        reject(code) 
      else
        resolve(code);
    }); 
  });

  function getPlankGYPI(gypFile) {
    return path.join( __dirname, '../def', gypFile );
  }
}

module.exports = generate;
