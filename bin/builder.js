var assert = require( 'assert' )
  , path = require( 'path' )
  , Promise = require( 'promise' );

function build(context, cb) {
  
  assert( context.hasOwnProperty( 'targetName' ) );
  assert( context.hasOwnProperty( 'tempDir' ) );

  return new Promise( function(resolve, reject) {
    
    spawnChild()
    .on( 'exit', function(code) {
      if (code) 
        reject(code);
      else
        resolve(code);
    });

    function spawnChild() {
      if (context.gcc) {
        var args = [ '-j', '-C', './' ]; 
        if (context.release) {
          args.push( 'BUILDTYPE=Release' );
        }
        else if (context.debug) {
          args.push( 'BUILDTYPE=Debug' );
        }

        return context.spawn( 'make', args, context.tempDir );
      }
      else 
      {
        var pathProject = path.join( context.testDir, context.tempDir, context.targetName + ".xcodeproj" );
        if (context.ide) {
          context.spawn( 'open', [ pathProject ] );
        }
        return context.spawn( 'xcodebuild', ['-project', pathProject ] );
      }
    }
  });
}

module.exports = build;