var assert = require( 'assert' )
  , path = require( 'path' )
  , cp = require( 'child_process' );

function generate( options, cb ) {

  assert( options.hasOwnProperty( 'testDir' ) );
  assert( options.hasOwnProperty( 'pathGYP' ) );

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
  }

  if (options.debug) {
    args.push( '--build=Debug' );  
  }
  else if (options.release) {
    args.push( '--build=Release' );
  }

  cp.spawn( 
    'gyp', 
    args, 
    {
      stdio: 'inherit',
      cwd: options.testDir
    })
  .on( 'exit', function( code ) {
    cb( code );
  });

  function getPlankGYPI(gypFile) {
    return path.join( __dirname, '../def', gypFile );
  }
}

module.exports = generate;
