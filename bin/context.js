var cp = require( 'child_process' )
  , path = require( 'path' ); 

function Context(program, pathJSON) {

  var instance = this
    , stdoutMode = program.verbose ? 'inherit' : 'pipe';
  
  this.pathJSON = path.basename( pathJSON );
  this.testDir = path.join( process.cwd(), path.dirname( pathJSON ) );
  this.tempDir = 'tmp';
  this.targetName = 'test';
  
  if (program.output) {
    this.tempDir = program.output;
  }

  this.xargs = [];
  if (program.xargs) {
    this.xargs = this.xargs.concat( program.xargs );
  }    

  this.spawn = (exec, args, cwd, resolve, reject) => {
    if (typeof cwd === 'undefined') {
      cwd = '.';
    }

    return cp.spawn( 
      exec,
      args, 
      { 
        stdio: stdoutMode,
        cwd: path.join( this.testDir, cwd ) 
      })
    .on( 'exit', (code) => {
      
      if (code)
        reject(code);
      else
        resolve();
    })
    .on( 'error', (err) => {
      
      console.log( 'close' ); 
      

      reject( err );
    });
  };
}

module.exports = Context;

