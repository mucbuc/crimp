var cp = require( 'child_process' )
  , Promise = require( 'promise' )
  , join = require( 'path' ).join;

function run(options) {
  return new Promise( function( resolve, reject) {

    var cwd = join(options.testDir, options.tempDir )
      , execPath = options.gcc ? join( 'build', 'out' ) : 'build';

      if (options.release) {
        execPath = join( execPath, 'Release');
      }
      else if (options.test) {
        execPath = join( execPath, 'Test');
      }
      else {
        execPath = join( execPath, 'Debug');
      }

      execPath = join( execPath, options.targetName );

      cp.spawn( 
        execPath,
        [], 
        { stdio: 'inherit', cwd: cwd } )
      .on( 'exit', function(code) {
        if (code)
          reject();
        else
          resolve();
      });
  });

}


module.exports = run;