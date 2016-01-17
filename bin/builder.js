var assert = require( 'assert' )
  , cp = require( 'child_process' )
  , path = require( 'path' )
  , Promise = require( 'promise' );

function build(context, cb) {
  
  assert( context.hasOwnProperty( 'targetName' ) );
  assert( context.hasOwnProperty( 'tempDir' ) );

  return new Promise( function(resolve, reject) {
    
    var child
      , pathProject = path.join( context.testDir, context.tempDir );
    
    if (context.gcc) {
      var args = [ '-j', '-C', './' ]; 
      if (context.release) {
        args.push( 'BUILDTYPE=Release' );
      }
      else if (context.debug) {
        args.push( 'BUILDTYPE=Debug' );
      }

      child = cp.spawn( 'make', args, { stdio: 'inherit', cwd: pathProject } );
    }
    else 
    {
      var pathProject = path.join( pathProject, context.targetName + ".xcodeproj" )
        , args = ['-project', pathProject ];
      
      child = cp.spawn( 'xcodebuild', args, { stdio: 'inherit', cwd: context.testDir } );
      if (context.ide) {
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