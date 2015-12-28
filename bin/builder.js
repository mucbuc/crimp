var assert = require( 'assert' )
  , cp = require( 'child_process' )
  , path = require( 'path' )
  , Promise = require( 'promise' );

function build(options, cb) {
  
  assert( options.hasOwnProperty( 'targetName' ) );
  assert( options.hasOwnProperty( 'buildDir' ) );

  return new Promise( function(resolve, reject) {
    
    if (options.gcc) {
      var args = [ '-j', '-C', './' ]; 
      if (options.release) {
        args.push( 'BUILDTYPE=Release' );
      }
      else if (options.debug) {
        args.push( 'BUILDTYPE=Debug' );
      }
      cp.spawn( 'make', args, { stdio: 'inherit', cwd: options.buildDir } )
      .on( 'exit', function(code) {
        if (code) 
          reject(code);
        else
          resolve(code);
      });
    }
    else 
    {
      resolve(0);
    }


  });
}

module.exports = build;