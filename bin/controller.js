var assert = require( 'assert' )
  , define = require( '../bin/definer' )
  , generate = require( '../bin/generator' )
  , build = require( '../bin/builder' )
  , fs = require( 'fs' )
  , path = require( 'path' )
  , cp = require( 'child_process' )
  , Printer = require( './printer' )
  , run = require( '../bin/runner' )
  , translate = require( '../bin/translator' )
  , Promise = require( 'promise' )
  , traverse = require( 'traverjs' )
  , successCounter = 0;

assert( typeof translate !== 'undefined' ); 

function buildProject( options, cb ) {
  
  assert( options.hasOwnProperty('pathJSON') );

  Printer.begin( 'define', options.pathJSON );

  define( options.pathJSON, options.testDir )
  .then( function(product) {
    
    var resultPath = path.join( options.testDir, options.buildDir, 'result.json' );

    Printer.finishGreen( 'define' ); 
      
    if (product.hasOwnProperty('opengl')) {
      options.opengl = true;
    }

    translateData()
    .then( function() {
      generateProject()
      .then( function() { 
        buildTarget()
        .then( function() {
          if (options.execute) {
            fs.unlink( resultPath, function() {
              executeTarget()
              .then( function() {
                readResults().then( function(results) {
                  cb(results.passed);
                })
                .catch(cb);
              })
              .catch(cb);
            } );
          }
          else {
            cb();
          } 
        }); 
      });
    });

    function readResults(cb) {
      return new Promise(function(resolve, reject) {
        fs.readFile( resultPath, function(err, data) {
          var obj = {};

          try {
            resolve( JSON.parse( data.toString() ) );
          }
          catch(err) {
            console.log( err );
            reject(err);
          }
        });
      }); 
    }

    function generateProject() {
      return new Promise(function(resolve, reject) {

        var dirGYP = path.join(options.testDir, options.buildDir)
        makePathIfNone( dirGYP, function() {

          options.nameGYP = options.targetName + ".gyp";
          options.pathGYP = path.join( dirGYP, options.nameGYP );
          writeGYP( product, options.pathGYP, function(error) {
            if (error) throw error;
            
            Printer.begin( 'generate', options.pathGYP );
            generate( options )
            .then( function() {
              Printer.finishGreen( 'generate' );
              resolve(); 
            })
            .catch(function(error) {
              Printer.finishRed( 'generate' );
              console.log(error);
              reject(); 
            });
          });
        });
      });
    }

    function buildTarget() {
      return new Promise(function(resolve,reject) {
        Printer.begin( 'build', options.pathGYP);
        build( options )
        .then( function() {
          Printer.finishGreen( 'build' );
          resolve(); 
        })
        .catch( function(stderr, stdout) {
          Printer.finishRed( 'build', stderr.toString() + stdout.toString() );
          reject();
        });
      });
      
    }

    function executeTarget() {
      return new Promise(function(resolve,reject) {
        Printer.begin( 'execute', options.targetName );

        run(options)
        .then( function() {
          Printer.finishGreen( 'execute' ); 
          resolve();
        })
        .catch( function() {
          Printer.finishRed( 'execute' );
          reject();
        });
      });
    }

    function translateData() {
      return new Promise( function(resolve, reject) {
        if (product.hasOwnProperty('data')) {
          var cppDir = path.join( 'src', 'data' );
          makePathIfNone( cppDir, function() {
            traverse( product.data, function(entry, next) {
              product.sources.push( path.join( 
                  '..',
                  cppDir,
                  path.basename(path.basename(entry) )
                ) + '.h'
              );
              entry = path.join( options.testDir, entry);
              Printer.begin( 'translate', entry ); 
              translate( entry, function() {
                Printer.finishGreen( 'translate' ); 
                next(); 
              });
            })
            .then( resolve )
            .catch( resolve );
          });
        }
        else {
          resolve();
        }
      });
    }

  })
  .catch( function(error) {
    Printer.finishRed( 'define' );
  });
}

function writeGYP(product, pathGYP, cb) {
  var gyp = {
        target_defaults: {
          target_name: 'test',
          type: 'executable',
          sources: product.sources,
          include_dirs: [ '../' ]
        }
      };
  fs.writeFile( 
      pathGYP, 
      JSON.stringify( gyp, null, 2 ),
      cb
  );
}

function makePathIfNone( path, cb ) {
  fs.exists(path, function(exists) {
    if (exists) 
      cb();
    else 
      fs.mkdir( path, [], cb ); 
  });
}

module.exports = buildProject;