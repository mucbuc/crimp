var assert = require( 'assert' )
  , define = require( '../node_modules/cstar/api' ).makeGYP
  , generate = require( '../bin/generator' )
  , path = require( 'path' )
  , Printer = require( './printer' )
  , run = require( '../bin/runner' )
  , translate = require( '../bin/translator' )
  , Promise = require( 'promise' )
  , traverse = require( 'traverjs' )
  , fs = require( 'fs.extra' );

assert( typeof translate !== 'undefined' ); 
assert( typeof define !== 'undefined' );

function buildProject( context, cb ) {

  var absPath
    , dirGYP = path.join(context.testDir, context.tempDir);

  assert( context.hasOwnProperty('pathJSON') );

  absPath = path.join( context.testDir, context.pathJSON );
  Printer.begin( 'unit', absPath ); 
  Printer.begin( 'define', absPath );

  process.chdir( dirGYP );

  define( path.join(context.testDir, context.pathJSON) )
  .then( (product) => {

    var resultPath = path.join( dirGYP, 'result.json' );

    Printer.finishGreen( 'define' ); 

    if (product.hasOwnProperty('opengl')) {
      context.opengl = true;
    }
    
    Printer.begin( 'copy files', dirGYP );

    copyFiles( dirGYP )
    .then( () => {
      
      Printer.finishGreen( 'copy files' );

      translateData()
      .then( () => {
        generateProject()
        .then( () => {
          if (context.execute) {
            fs.unlink( resultPath, () => {
              executeTarget()
              .then( () => {
                Printer.finishGreen( 'unit' );
                readResults().then( (results) => {
                  cb(results.passed);
                })
                .catch(cb);
              })
              .catch(cb);
            } );
          }
          else {
            Printer.finishGreen( 'unit' );
            cb();
          } 
        })
        .catch( (err) => {
          process.exit( 1 );
        });
      })
      .catch( (err) => {
        throw err;
      });
    })
    .catch( (err) => {
      throw err;
    });

    function copyFiles(tmpPath) {
      return new Promise( (resolve, reject) => {
        var source = path.join( __dirname, '..', 'lib', 'asserter', 'src' )
          , dest = path.join( tmpPath, 'src' );

        fs.copyRecursive( 
          source, 
          dest,
          (error) => {
            //if (error) throw error;
            resolve();
          }
        ); 
      });
    }

    function readResults(cb) {
      return new Promise( (resolve, reject) => {
        fs.readFile( resultPath, (err, data) => {
          var obj = {};
          if (err) {
            reject(err);
          }
          else {
            try {
              resolve( JSON.parse( data.toString() ) );
            }
            catch(err) {
              console.error( err );
              reject(err);
            }
          }
        });
      }); 
    }

    function generateProject() {
      return new Promise( (resolve, reject) => {

        makePathIfNone( dirGYP, () => {

          context.nameGYP = context.targetName + ".gypi";
          context.pathGYP = path.join( dirGYP, context.nameGYP );
          writeGYP( product, context.pathGYP, (error) => {
            if (error) throw error;
            
            Printer.begin( 'generate', context.pathGYP );
            generate( context )
            .then( () => {
              Printer.finishGreen( 'generate' );
              resolve(); 
            })
            .catch( (error) => {
              Printer.finishRed( 'generate' );
              reject(error); 
            });
          });
        });
      });
    }

    function executeTarget() {
      return new Promise( (resolve,reject) => {
        Printer.begin( 'execute', context.targetName );

        run(context)
        .then( () => {
          Printer.finishGreen( 'execute' ); 
          resolve();
        })
        .catch( () => {
          Printer.finishRed( 'execute' );
          reject();
        });
      });
    }

    function translateData() {
      return new Promise( (resolve, reject) => {
        if (product.hasOwnProperty('data')) {
          
          var cppDir = path.join(dirGYP, 'src', 'data');

          makePathIfNone( cppDir, () => {

            traverse( product.data, (entry, next) => {
              var fileName = path.basename(path.basename(entry)) + '.h'
                , pathOut = path.join( cppDir, fileName );

              product.sources.push( path.join( 
                  cppDir,
                  fileName
                )
              );

              entry = path.join( dirGYP, entry);

              Printer.begin( 'translate', entry ); 
              translate( entry, pathOut, () => {
                Printer.finishGreen( 'translate' ); 
                next(); 
              });
            })
            .then( resolve )
            .catch( reject );
          });
        }
        else {
          resolve();
        }
      });
    }
  })
  .catch( (error) => {
    
    console.log( 'error', error );
    
    Printer.finishRed( 'define' );
    process.exit( 1 );
  });
}

function writeGYP(product, pathGYP, cb) {
  fs.writeFile( 
      pathGYP, 
      product,
      cb
  );
}

function makePathIfNone( path, cb ) {
  fs.exists(path, (exists) => {
    if (exists) 
      cb();
    else 
      fs.mkdirp( path, [], cb ); 
  });
}

module.exports = buildProject;