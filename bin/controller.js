var assert = require( 'assert' )
  , define = require( '../bin/definer' )
  , generate = require( '../bin/generator' )
  , fs = require( 'fs' )
  , path = require( 'path' )
  , Printer = require( './printer' )
  , run = require( '../bin/runner' )
  , translate = require( '../bin/translator' )
  , Promise = require( 'promise' )
  , traverse = require( 'traverjs' )
  , successCounter = 0
  , fs = require( 'fs.extra' );

assert( typeof translate !== 'undefined' ); 

function buildProject( context, cb ) {

  var absPath;

  assert( context.hasOwnProperty('pathJSON') );

  absPath = path.join( context.testDir, context.pathJSON );
  Printer.begin( 'unit', absPath ); 
  Printer.begin( 'define', absPath );

  define( context.pathJSON, context.testDir )
  .then( function(product) {
    
    var dirGYP = path.join(context.testDir, context.tempDir)
      , resultPath = path.join( dirGYP, 'result.json' )
      , source = path.join( __dirname, '..', 'lib', 'asserter', 'src' )
      , dest = path.join( dirGYP, 'src' );

    Printer.finishGreen( 'define' ); 
    
    fs.copyRecursive( 
      source, 
      dest,
      function(error) {
//        if (error) throw error;
      }
    ); 

    if (product.hasOwnProperty('opengl')) {
      context.opengl = true;
    }

    translateData()
    .then( function() {
      generateProject()
      .then( function() {
        if (context.execute) {
          fs.unlink( resultPath, function() {
            executeTarget()
            .then( function() {
              Printer.finishGreen( 'unit' );
              readResults().then( function(results) {
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
      });
    });

    function readResults(cb) {
      return new Promise(function(resolve, reject) {
        fs.readFile( resultPath, function(err, data) {
          var obj = {};
          if (err) {
            reject(err);
          }
          else {
            try {
              resolve( JSON.parse( data.toString() ) );
            }
            catch(err) {
              console.log( err );
              reject(err);
            }
          }
        });
      }); 
    }

    function generateProject() {
      return new Promise(function(resolve, reject) {

        makePathIfNone( dirGYP, function() {

          context.nameGYP = context.targetName + ".gyp";
          context.pathGYP = path.join( dirGYP, context.nameGYP );
          writeGYP( product, context.pathGYP, function(error) {
            if (error) throw error;
            
            Printer.begin( 'generate', context.pathGYP );
            generate( context )
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

    function executeTarget() {
      return new Promise(function(resolve,reject) {
        Printer.begin( 'execute', context.targetName );

        run(context)
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
              entry = path.join( context.testDir, entry);
              Printer.begin( 'translate', entry ); 
              translate( entry, function() {
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