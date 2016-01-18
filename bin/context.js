var cp = require( 'child_process' )
  , path = require( 'path' ); 

function Context(program, pathJSON) {

  var instance = this; 
  
  this.pathJSON = path.basename( pathJSON );
  this.testDir = path.join( process.cwd(), path.dirname( pathJSON ) );
  this.tempDir = 'tmp';
  this.targetName = 'test';
  
  if (program.release) {
    this.release = true;
  }
  else if (program.debug) {
    this.debug = true;
  } 
  else {
    this.test = true;
    this.execute = true;
  }

  if (program.output) {
    this.tempDir = program.output;
  }

  if (program.gcc) {
    this.gcc = true;
  }

  if (program.execute) {
    this.execute = true;
  }

  if (program.ide) {
    this.ide = program.ide;
  }

  this.stdioMode = program.verbose ? 'inherit' : 'pipe';
  
  this.spawn = function(exec, args, cwd) {
    if (typeof cwd === 'undefined') {
      cwd = '.';
    }
    return cp.spawn( 
      exec,
      args, 
      { 
        stdio: instance.stdioMode, 
        cwd: path.join( this.testDir, cwd ) 
      });
  };
}

module.exports = Context;

