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
        
        traverse( content, (prop, next)=>{
          
          if (prop.hasOwnProperty('import')) {
            handleImports( prop.import, next);
          }
          else if (prop.hasOwnProperty('data')) {
            handleData( prop.data, next);
          }
          else if (prop.hasOwnProperty('sources')) {
            handleSources( prop.sources, next );
          }
          else {
            Object.assign( product, prop );
            next();
          }
        })
        .then( ()=>{
          resolve(product);
        } );
        
        function handleData(data, cb) {
          product.data = [];
          traverse( data, (dataPath, next) => {
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

        function handleSources(sources, cb) {
          traverse( sources, (source, next) => {
            product.sources.push( path.join( '..', path.dirname(fileJSON), source ) );
            next();
          })
          .then( cb )
          .catch( cb ); 
        }

      });
    });
  }
}

module.exports = define;
