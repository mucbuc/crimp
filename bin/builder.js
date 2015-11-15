var cp = require( 'child_process' )
  , path = require( 'path' )
  , Promise = require( 'promise' );

function build(options, cb) {
  
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
        child = cp.spawn( 'make', args, { stdio: 'inherit', cwd: options.buildDir } );
      }
      else 
      {
        var pathProject = path.join( options.buildDir, options.buildDir, options.targetName + ".xcodeproj" )
          , args = ['-project', pathProject ];
        child = cp.spawn( 'xcodebuild', args, { stdio: 'inherit' } );
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