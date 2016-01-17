var cp = require( 'child_process' )
  , path = require( 'path' ); 

function Context(program) {

  var instance = this; 

  this.tempDir = 'tmp';
  this.targetName = 'test';
  this.testDir = '.';
  this.pathJSON = './test.json';
  
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

