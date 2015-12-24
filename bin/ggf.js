#!/usr/bin/env node

/*
  
objective: 
  generate gyp file
*/ 

var fs = require( 'fs' )
  , path = require( 'path' )
  , util = require( 'util' )
  , assert = require( 'assert' )
  , Promise = require( 'promise' ); 

function defineGYP(pathJSON) {

  var product = {
        'sources': [],
        'data': []
      }
    , buildDir = path.dirname(pathJSON);

  assert( fs.existsSync( pathJSON ), "project json missing: " + pathJSON ); 
  
  return processDependencies( pathJSON, '' );

  function processDependencies(fileJSON, basePath) {
    
    return new Promise( function(resolve, reject) {
      fs.readFile( fileJSON, function(err, data) {
        var content;
        if (err) throw "project json missing: " + fileJSON + " cwd: " + process.cwd();
        
        content = JSON.parse( data.toString() );
        
        if (content.hasOwnProperty('sources')) {
          content.sources.forEach(function(source, index, array) {
            product.sources.push(
              path.join( '..', path.dirname(fileJSON), source ) 
            );
          });
        }

        if (    content.hasOwnProperty('data')
            &&  content.data.length) {

          content.data.forEach(function(dataPath) {
            product.data.push( path.join( 
              '..', 
              path.dirname(fileJSON), 
              dataPath )
            ); 
          });   
        }

        if (  content.hasOwnProperty('import')
          &&  content.import.length) {
          content.import.forEach( function( item, index, array ) {
            processDependencies( path.join( buildDir, item ), path.dirname(fileJSON) )
            .then( function() {
              if (index == array.length - 1) {
                resolve(product); 
              }
            });
          });
        }
        else {
          resolve(); 
        }
      });
    } );
  }
}

module.exports = defineGYP;