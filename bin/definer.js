/*
objective:
  - create product object mapping properties with types 
  - read and parse json
*/

var assert = require( 'assert' )
  , path = require( 'path' )
  , fs = require( 'fs' )
  , Promise = require( 'promise' )
  , traverse = require( 'traverjs' );

function define(pathJSON, pathBase, objReader) {

  var product = {
        'sources': []
      }
    , imported = [];

  fs.readFile( path.join( __dirname, '../lib/asserter/def.json' ), (err, data) => {
    if (err) throw err;
    product.sources = product.sources.concat(JSON.parse(data.toString()).sources);
  });

  if (typeof objReader === 'undefined') {
    objReader =  (filePath, cb) => {
      fs.readFile(filePath, (err, data) => {
        if (err) throw err;
        cb( JSON.parse( data.toString() ) );
      });
    };
  }

  return processDependencies( pathJSON, pathBase );  

  function processDependencies(fileJSON, pathBase) {
    
    return new Promise( (resolve, reject) => {
      objReader( path.join(pathBase, fileJSON), (content) => {
        
        assert( typeof content === 'object' );
        
        if (    content.hasOwnProperty('opengl') 
            &&  content.opengl) {
          product.opengl = true;
        }
        
        if (content.hasOwnProperty('import')) {
          handleImports( content.import, () => {
            handleSources( () => {
              handleData( () => {
                resolve(product); 
              } ); 
            });
          });
        }
        else {
          handleSources( () => {
            handleData( () => {
              resolve(product); 
            } ); 
          });
        }

        function handleData(cb) {
          if ( content.hasOwnProperty('data')) {
            product.data = [];
            traverse( content.data, (dataPath, next) => {
              var absPath = path.join( 
                    path.dirname(fileJSON), 
                    dataPath 
                  );
              product.data.push( absPath );
              next();
            })
            .then( cb )
            .catch(cb); 
          }
          else {
            cb();
          }
        }
        
        function handleImports(imports, cb) {
          traverse( imports, ( item, next ) => {
            if (imported.indexOf(item) == -1) {
              imported.push(item);
              processDependencies( item, pathBase )
              .then( next )
              .catch( reject );
            }
            else {
              next();
            }
          })
          .then( cb )
          .catch( cb );
        }

        function handleSources(cb) {
          if (content.hasOwnProperty('sources')) {
            traverse( content.sources, (source, next) => {
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
