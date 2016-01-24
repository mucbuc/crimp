var assert = require( 'assert' )
  , path = require( 'path' )
  , Promise = require( 'promise' );

function generate( context ) {

  assert( context.hasOwnProperty( 'testDir' ) );
  assert( context.hasOwnProperty( 'pathGYP' ) );
  assert( context.hasOwnProperty( 'tempDir' ) );

  return new Promise(function(resolve, reject) {
    var args = [
          context.nameGYP
        ];  

    if (context.gcc) {
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
    }
    
    if (context.debug) {
      args.push( '--build=Debug' );  
    }
    else if (context.release) {
      args.push( '--build=Release' );
    }
    else {
      args.push( '--build=Test' );
    }
    
    if (context.opengl) {
      args.push( '--include=' + getPlankGYPI( 'opengl.gypi' ) );
    }

    context.spawn( 
      'gyp', 
      args, 
      context.tempDir
    )
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
