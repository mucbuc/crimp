var assert = require( 'assert' )
  , define = require( '../bin/definer' )
  , generate = require( '../bin/generator' )
  , build = require( '../bin/builder' )
  , fs = require( 'fs' )
  , path = require( 'path' )
  , cp = require( 'child_process' )
  , Printer = require( './printer' )
  , run = require( '../bin/runner' )
  , translate = require( '../bin/translator' );

assert( typeof translate !== 'undefined' ); 

function buildProject( options, cb ) {
  
  assert( options.hasOwnProperty('pathJSON') );


  Printer.begin( 'define', options.pathJSON );

  define( options.pathJSON )
  .then( function(product) {
    Printer.finishGreen( 'define' );

    console.log( product ); 

    if (product.hasOwnProperty('data'))
    {
      product.data.forEach(function(entry) {
        translate( entry ); 
      });
    }

    makePathIfNone( options.buildDir, function() {

      options.pathGYP = path.join( options.buildDir, options.targetName + ".gyp" );
      writeGYP( product, options.pathGYP, function(error) {
        if (error) throw error;
        Printer.begin( 'generate', options.pathGYP );
        generate( options )
        .then( function() {
          Printer.finishGreen( 'generate' );
          Printer.begin( 'build', options.pathGYP);
          build( options )
          .then( function() {
            Printer.finishGreen( 'build' );
            if (options.execute) {
              Printer.begin( 'execute', options.targetName );
              run(options)
              .then( function(stdout, stderr) {
                process.stdout.write( stdout ); 
                process.stderr.write( stderr );
                Printer.finishGreen( 'execute' ); 
                cb();
              })
              .catch( function(err) {
                throw err; 
              });
            }
            else {
              cb();
            }
          })
        })
        .catch(function(error) {
          Printer.finishRed( 'generate' );
          console.log(error);
        });
      });
    });
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