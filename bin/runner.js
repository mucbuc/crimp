var Promise = require( 'promise' )
  , join = require( 'path' ).join;

function run(context) {
  return new Promise( function( resolve, reject) {

    var execPath = context.gcc ? 'out' : 'build';
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

    context.spawn( execPath, context.xargs, context.tempDir, resolve, reject );
  });

}


module.exports = run;