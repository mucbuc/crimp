var assert = require( 'assert' )
  , path = require( 'path' )
  , Promise = require( 'promise' );

function generate( context ) {

  assert( context.hasOwnProperty( 'testDir' ) );
  assert( context.hasOwnProperty( 'pathGYP' ) );
  assert( context.hasOwnProperty( 'tempDir' ) );

  return new Promise(function(resolve, reject) {
    var args = [
          '--depth=.',
          context.nameGYP
        ];  

    if (context.gcc) {
      args.push( '--include=' + includePath( 'cpp11-gcc.gypi' ) );
      args.push( '--format=make' ); 
    }
    else {
      args.push( '--include=' + includePath( 'cpp11.gypi' ) );
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
      args.push( '--include=' + includePath( 'opengl.gypi' ) );
    }

    context.spawn( 'gyp', args, context.tempDir, resolve, reject )
    .on( 'error', function(error) {
      console.log( error ); 
    });
  });

  function includePath(gypFile) {
    return path.join( __dirname, '../def', gypFile );
  }
}

module.exports = generate;
