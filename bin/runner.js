var cp = require( 'child_process' )
  , Promise = require( 'promise' )
  , join = require( 'path' ).join;

function run(options) {
  return new Promise( function( resolve, reject) {
    if (options.gcc) {
      if (options.release) {
        runBuild( './build/out/Release/test', resolve, reject );
      }
      else if (options.test) {
        runBuild( './build/out/Test/test', resolve, reject );
      }
      else {
        runBuild( './build/out/Debug/test', resolve, reject ); 
      }
    }
    else {
      if (options.release) {
        runBuild( './build/build/Release/test', resolve, reject );
      }
      else if (options.test) {
        runBuild( './build/build/Test/test', resolve, reject ); 
      }
      else {
        runBuild( './build/build/Debug/test', resolve, reject );
      }
    }
  });

  function runBuild( path, resolve, reject ) {
    cp.spawn( path, [], { stdio: 'inherit', cwd: options.testDir } )
    .on( 'exit', function(code) {
      if (code)
        reject();
      else
        resolve();
    }); 
  }
}


module.exports = run;