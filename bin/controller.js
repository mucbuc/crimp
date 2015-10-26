var define = require( '../bin/definer.js' )
  , generate = require( '../bin/generator.js' )
  , build = require( '../bin/builder.js' )
  , fs = require( 'fs' )
  , path = require( 'path' );

function buildProject( pathJSON, cb ) {
  var options = { 
        buildDir: 'build',
        targetName: 'test',
        testDir: '.'
    };

  define( pathJSON, function(product) {
    console.log( 'product', product );
    makePathIfNone( options.buildDir, function() {
      options.pathGYP = path.join( options.buildDir, options.targetName + ".gyp" );
      writeGYP( product, options.pathGYP, function() {
        generate( options, function() {
          build( options, cb );
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
      null,
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