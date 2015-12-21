var assert = require( 'assert' )
  , path = require( 'path' )
  , fs = require( 'fs' )
  , Promise = require( 'promise' );

function define(pathJSON) {

  var buildDir = path.dirname(pathJSON)
    , product = {
        'sources': [],
        'data': []
      };

  return processDependencies( pathJSON, '' );

  function processDependencies(fileJSON, basePath) {
    
    return new Promise( function(resolve, reject) {

      fs.readFile( fileJSON, function(err, data) {
        var content;

        if (err) throw err;
  
        content = JSON.parse( data.toString() );

        handleSources( function() {
          handleImports( function() {
            handleData( function() {
              resolve(product); 
            } ); 
          });
        });

        function handleData(cb) {
          if (    content.hasOwnProperty('data')
              &&  content.data.length) {
            content.data.forEach(function(dataPath, index, array) {
              var absPath = path.join( 
                    '..', 
                    path.dirname(fileJSON), 
                    dataPath 
                  );
              product.data.push( absPath );

              if (index == array.length - 1) {
                cb();
              }
            }); 
          }
          else {
            cb();
          }
        }
        
        function handleImports(cb) {
          if (  content.hasOwnProperty('import')
            &&  content.import.length) {
            content.import.forEach( function( item, index, array ) {
              processDependencies( path.join( buildDir, item ), path.dirname(fileJSON) )
              .then( function() {
                if (index == array.length - 1) {
                  cb(); 
                }
              })
              .catch( reject );
            });
          }
          else {
            cb(); 
          }
        }

        function handleSources(cb) {
          if (  content.hasOwnProperty('sources')
            &&  content.sources.length) {
            content.sources.forEach(function(source, index, array) {
              product.sources.push( path.join( '..', path.dirname(fileJSON), source ) );
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
