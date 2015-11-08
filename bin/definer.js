var assert = require( 'assert' )
  , path = require( 'path' )
  , fs = require( 'fs' )
  , Promise = require( 'promise' );

function define(pathJSON) {

  var product = {
        'sources': []
      }
    , buildDir = path.dirname(pathJSON);

  return processDependencies( pathJSON, '' );
  
  function processDependencies(fileJSON, basePath) {
    
    return new Promise( function(resolve, reject) {
      fs.readFile( fileJSON, function(err, data) {
        if (err) reject( err );
  
        var content = JSON.parse( data.toString() );

        handleSources( function() {
          handleImports( resolve ); 
        });

        function handleImports(cb) {
          if (  content.hasOwnProperty('import')
            &&  content.import.length) {
            content.import.forEach( function( item, index, array ) {
              processDependencies( path.join( buildDir, item ), path.dirname(fileJSON) )
              .then( function() {
                if (index == array.length - 1) {
                  cb(product); 
                }
              })
              .catch( reject );
            });
          }
          else {
            cb(product); 
          }
        }

        function handleSources(cb) {
          if (  content.hasOwnProperty('sources')
            &&  content.sources.length) {
            content.sources.forEach(function(source, index, array) {
              product.sources = product.sources.concat( path.join( '..', path.dirname(fileJSON), source ) );
              if (index == array.length - 1) {
                cb();
              }
            });
          }
          else {
            cb();
          }
        }

      });
    } );
  }
}

module.exports = define;
