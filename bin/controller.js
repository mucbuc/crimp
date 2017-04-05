var assert = require( 'assert' )
  , define = require( '../node_modules/cstar/api' ).makeGYP
  , generate = require( '../bin/generator' )
  , path = require( 'path' )
  , Printer = require( './printer' )
  , run = require( '../bin/runner' )
  , traverse = require( 'traverjs' )
  , fs = require( 'fs.extra' );

assert( typeof define !== 'undefined' );

function buildProject( context, cb ) {

  var absPath
    , dirGYP = context.testDir;

  assert( context.hasOwnProperty('pathJSON') );

  absPath = path.join( context.testDir, context.pathJSON );
  Printer.begin( 'unit', absPath ); 
  Printer.begin( 'define', absPath );

  process.chdir( dirGYP );

  console.log( 'context.pathJSON', context.pathJSON );

  define( context.pathJSON )
  .then( (product) => {

    Printer.finishGreen( 'define' ); 
    
    generateProject()
    .then( () => {
      Printer.finishGreen( 'unit' );
      cb();
    })
    .catch( (err) => {
      process.exit( 1 );
    });

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