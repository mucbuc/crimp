var define = require( '../bin/definer.js' )
  , generate = require( '../bin/generator.js' )
  , build = require( '../bin/builder.js' )
  , fs = require( 'fs' )
  , path = require( 'path' )
  , cp = require( 'child_process' );

function buildProject( options, cb ) {
  
  define( options.pathJSON )
  .then( function(product) {
    
    makePathIfNone( options.buildDir, function() {

      options.pathGYP = path.join( options.buildDir, options.targetName + ".gyp" );
      writeGYP( product, options.pathGYP, function(error) {
        if (error) throw error;
        
        generate( options )
        .then( function() {
          build( options ).then( cb );
        })
        .catch(function(error) {
          console.log(error);
        });
      });
    });
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