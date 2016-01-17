var cp = require( 'child_process' )
  , Promise = require( 'promise' )
  , join = require( 'path' ).join;

function run(context) {
  return new Promise( function( resolve, reject) {

    var cwd = join(context.testDir, context.tempDir )
      , execPath = context.gcc ? 'out' : 'build';

      if (context.release) {
        execPath = join( execPath, 'Release');
      }
      else if (context.test) {
        execPath = join( execPath, 'Test');
      }
      else {
        execPath = join( execPath, 'Debug');
      }

      execPath = join( execPath, context.targetName );

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