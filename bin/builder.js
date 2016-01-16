var assert = require( 'assert' )
  , cp = require( 'child_process' )
  , path = require( 'path' )
  , Promise = require( 'promise' );

function build(options, cb) {
  
  assert( options.hasOwnProperty( 'targetName' ) );
  assert( options.hasOwnProperty( 'buildDir' ) );
  assert( options.hasOwnProperty( 'tempDir' ) );

  return new Promise( function(resolve, reject) {
    
    var child;
    if (options.gcc) {
      var args = [ '-j', '-C', './' ]; 
      if (options.release) {
        args.push( 'BUILDTYPE=Release' );
      }
      else if (options.debug) {
        args.push( 'BUILDTYPE=Debug' );
      }
      child = cp.spawn( 'make', args, { stdio: 'inherit', cwd: path.join( options.testDir, options.tempDir ) } );
    }
    else 
    {
      var pathProject = path.join( options.tempDir, options.buildDir, options.targetName + ".xcodeproj" )
        , args = ['-project', pathProject ];
      
      child = cp.spawn( 'xcodebuild', args, { stdio: 'inherit', cwd: options.testDir } );
      if (options.ide) {
        cp.spawn( 'open', [ pathProject ] );
      }
    }

    child.on( 'exit', function(code) {
      if (code) 
        reject(code);
      else
        resolve(code);
    });
  });
}

module.exports = build;