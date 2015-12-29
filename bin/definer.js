/*
objective:
  - create product object associating properties with types 
  - read and parse json
*/

var assert = require( 'assert' )
  , path = require( 'path' )
  , fs = require( 'fs' )
  , Promise = require( 'promise' )
  , traverse = require( 'traverjs' );

function define(pathJSON, objReader) {

  var buildDir
    , product = {
        'sources': [],
        'data': []
      };

  if (typeof objReader === 'undefined') {
    objReader = function(filePath, cb) {
      fs.readFile(filePath, function(err, data) {
        if (err) throw err;
        cb( JSON.parse( data.toString() ) );
      });
    };
  }

  buildDir = path.dirname(pathJSON);

  return processDependencies( pathJSON, '' );

  function processDependencies(fileJSON, basePath) {
    
    return new Promise( function(resolve, reject) {

      objReader( fileJSON, function(content) {
        assert( typeof content === 'object' );
        if (    content.hasOwnProperty('opengl') 
            &&  content.opengl) {
          product.opengl = true;
        }
        
        handleSources( function() {
          handleImports( function() {
            handleData( function() {
              resolve(product); 
            } ); 
          });
        });

        function handleData(cb) {
          if ( content.hasOwnProperty('data')) {
            traverse( content.data, function(dataPath, next) {
              var absPath = path.join( 
                    path.dirname(fileJSON), 
                    dataPath 
                  );
              product.data.push( absPath );
              next();
            })
            .then( cb ); 
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
          if (content.hasOwnProperty('sources')) {
            traverse( content.sources, function(source, next) {
              product.sources.push( path.join( '..', path.dirname(fileJSON), source ) );
              next();
            })
            .then( cb )
            .catch( cb ); 
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
