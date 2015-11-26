var cp = require( 'child_process' )
  , Promise = require( 'promise' );

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
}

function runBuild( path, resolve, reject ) {
  cp.execFile( path, function(err, stdout, stderr) {
    if(err) {
      reject( err );
    }
    else {
      resolve( stdout, stderr ); 
    }
  } );
}

module.exports = run;