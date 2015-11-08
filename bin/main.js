#!/usr/bin/env node

var define = require( './definer' )
  , path = require( 'path' )
  , fs = require( 'fs' );

define( path.join( __dirname, '../test/test.json' ), function(product) {
    var gyp = {
        target_defaults: {
            target_name: 'test',
            type: 'executable',
            sources: product.sources,
            include_dirs: [ '../' ]
        }
      };

      console.log( JSON.stringify( gyp, null, 2 ) ); 

    fs.writeFile( 
        path.join( __dirname, '../test/build/test.gyp' ), 
        JSON.stringify( gyp, null, 2 ),
        null,
        function() {
            console.log( 'done' );
        }); 
});