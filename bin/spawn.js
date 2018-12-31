const cp = require("child_process");

function spawn(command, args, options = {}) {
  return new Promise((resolve, reject) => {
    let child = cp
      .spawn(command, args, options)
      .on("error", error => {
        reject(error);
      })
      .on("exit", code => {
        resolve(code);
      });
    child.stderr.on("data", data => {
      process.stderr.write(data);
    });
    if (options.hasOwnProperty("onData")) {
      child.stdout.on("data", data => {
        options.onData(data);
      });
    }
  });
}

module.exports = spawn;
