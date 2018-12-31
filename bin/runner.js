const join = require("path").join,
  spawn = require("./spawn"),
  path = require("path");

function run(context) {
  if (!context.execute) {
    return Promise.resolve(0);
  }
  return new Promise((resolve, reject) => {
    let execPath = context.gcc ? "out" : "build";
    if (context.release) {
      execPath = join(execPath, "Release");
    } else if (context.test) {
      execPath = join(execPath, "Test");
    } else {
      execPath = join(execPath, "Debug");
    }
    let cwd = path.join(context.testDir, context.tempDir),
      cmd = path.join(execPath, context.targetName);
    spawn( cmd, context.xargs,
		    {
      cwd,
      onData: data => {
        process.stdout.write(data); 
	}
		    })
      .then(resolve)
      .catch(reject);
  });
}

module.exports = run;
