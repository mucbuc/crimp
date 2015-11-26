var assert = require( 'assert' )
  , path = require( 'path' )
  , cp = require( 'child_process' )
  , Promise = require( 'promise' );

function generate( options ) {

  assert( options.hasOwnProperty( 'testDir' ) );
  assert( options.hasOwnProperty( 'pathGYP' ) );

  console.log( options );

  return new Promise(function(resolve, reject) {
    var builDir = path.dirname( options.pathGYP )
      , args = [
          options.pathGYP,
          '--generator-output=' + builDir
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

    console.log( 'gyp args: ', args );
    console.log( 'options.testDir: ', options.testDir );
    console.log( 'process.cwd: ', process.cwd() );

    cp.spawn( 
      'gyp', 
      args, 
      {
        stdio: 'inherit'
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
