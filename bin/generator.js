var assert = require("assert"),
  path = require("path"),
  spawn = require("./spawn");

function generate(context) {
  assert(context.hasOwnProperty("testDir"));
  assert(context.hasOwnProperty("pathGYP"));
  assert(context.hasOwnProperty("tempDir"));

  return new Promise((resolve, reject) => {
    var args = ["--depth=.", context.nameGYP];

    if (context.gcc) {
      args.push("--include=" + includePath("cpp11-gcc.gypi"));
      args.push("--format=make");
    } else {
      args.push("--include=" + includePath("cpp11.gypi"));
    }

    if (context.debug) {
      args.push("--build=Debug");
    } else if (context.release) {
      args.push("--build=Release");
    } else {
      args.push("--build=Test");
    }

    if (context.opengl) {
      args.push("--include=" + includePath("opengl.gypi"));
    }
    spawn("gyp", args, {
      cwd: path.join(context.testDir, context.tempDir)
    })
    .then(resolve)
    .catch(reject);
});

  function includePath(gypFile) {
    return path.join(__dirname, "../def", gypFile);
  }
}

module.exports = generate;
