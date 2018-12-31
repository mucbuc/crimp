var assert = require("assert"),
  define = require("gyp-import"),
  generate = require("../bin/generator"),
  path = require("path"),
  run = require("../bin/runner"),
  translate = require("../bin/translator"),
  Promise = require("promise"),
  traverse = require("traverjs"),
  fs = require("fs.extra");

assert(typeof translate !== "undefined");
assert(typeof define !== "undefined");

function buildProject(context, cb) {
  var absPath,
    dirGYP = path.join(context.testDir, context.tempDir);
  const Printer = context.verbose ? require("./printer") : require("./silent");
  assert(context.hasOwnProperty("pathJSON"));

  absPath = path.join(context.testDir, context.pathJSON);
  Printer.begin("unit", absPath);
  Printer.begin("define", absPath);

  fs.mkdirRecursiveSync(dirGYP);
  const previousDir = process.cwd();
  process.chdir(dirGYP);

  define([
    path.join(context.testDir, context.pathJSON),
    path.join(__dirname, "../lib/asserter/def.json")
  ])
    .then(product => {
      var resultPath = path.join(dirGYP, "result.json");
      Printer.finishGreen("define");

      if (product.hasOwnProperty("opengl")) {
        context.opengl = true;
      }

      Printer.begin("copy files", dirGYP);

      copyFiles(dirGYP).then(() => {
        Printer.finishGreen("copy files");
        translateData().then(() => {
          process.chdir(previousDir);
          generateProject().then(code => {
            fs.unlink(resultPath, () => {
              executeTarget()
                .then(() => {
                  Printer.finishGreen("unit");
                  readResults()
                    .then(results => {
                      cb(results.passed);
                    })
                    .catch(cb);
                })
                .catch(cb);
            });
          });
        });
      });

      function copyFiles(tmpPath) {
        return new Promise((resolve, reject) => {
          var source = path.join(__dirname, "..", "lib", "asserter", "src"),
            dest = path.join(tmpPath, "src");

          fs.copyRecursive(source, dest, error => {
            //if (error) throw error;
            resolve();
          });
        });
      }

      function readResults(cb) {
        return new Promise((resolve, reject) => {
          fs.readFile(resultPath, (err, data) => {
            var obj = {};
            if (err) {
              reject(err);
            } else {
              try {
                resolve(JSON.parse(data.toString()));
              } catch (err) {
                console.error(err);
                reject(err);
              }
            }
          });
        });
      }

      function generateProject() {
        return new Promise((resolve, reject) => {
          makePathIfNone(dirGYP, () => {
            context.nameGYP = context.targetName + ".gyp";
            context.pathGYP = path.join(dirGYP, context.nameGYP);
            writeGYP(product, context.pathGYP, error => {
              if (error) throw error;

              Printer.begin("generate", context.pathGYP);
              generate(context)
                .then(() => {
                  Printer.finishGreen("generate");
                  resolve();
                })
                .catch(error => {
                  Printer.finishRed("generate");
                  console.error(error);
                  reject();
                });
            });
          });
        });
      }

      function executeTarget() {
        return new Promise((resolve, reject) => {
          Printer.begin("execute", context.targetName);

          run(context)
            .then(() => {
              Printer.finishGreen("execute");
              resolve();
            })
            .catch(error => {
              console.log(error);
              Printer.finishRed("execute");
              reject();
            });
        });
      }
      function translateData() {
        return new Promise((resolve, reject) => {
          if (product.hasOwnProperty("data")) {
            var cppDir = path.join(dirGYP, "src", "data");

            makePathIfNone(cppDir, () => {
              traverse(product.data, (entry, next) => {
                var fileName = path.basename(path.basename(entry)) + ".h",
                  pathOut = path.join(cppDir, fileName);

                product.sources.push(path.join(cppDir, fileName));

                entry = path.join(dirGYP, entry);

                Printer.begin("translate", entry);
                translate(entry, pathOut, () => {
                  Printer.finishGreen("translate");
                  next();
                });
              })
                .then(resolve)
                .catch(reject);
            });
          } else {
            resolve();
          }
        });
      }
    })
    .catch(error => {
      Printer.finishRed("define");
    });
}

function writeGYP(product, pathGYP, cb) {
  var gyp = {
    target_defaults: {
      target_name: "test",
      type: "executable",
      sources: product.sources,
      include_dirs: ["../"]
    }
  };
  fs.writeFile(pathGYP, JSON.stringify(gyp, null, 2), cb);
}

function makePathIfNone(path, cb) {
  fs.exists(path, exists => {
    if (exists) cb();
    else fs.mkdirp(path, [], cb);
  });
}

module.exports = buildProject;
