var assert = require( 'assert' )
  , cp = require( 'child_process' )
  , Promise = require( 'promise' )
  , join = require( 'path' ).join
  , Context = require( './context' );

assert( typeof Context !== 'undefined' ); 

function run(context) {
  return new Promise( function( resolve, reject) {

    var execPath = context.gcc ? 'out' : 'build'
      , executer = new Context(context); 

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

    executer.spawn(  
      execPath,
      [], 
      context.tempDir
    )
    .on( 'exit', function(code) {
      if (code)
        reject();
      else
        resolve();
    });
  });
}


module.exports = run;