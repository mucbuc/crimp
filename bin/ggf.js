#!/usr/bin/env node

/*
  
objective: 
  generate gyp file
*/ 

var fs = require( 'fs' )
  , path = require( 'path' )
  , util = require( 'util' )
  , assert = require( 'assert' )
  , Printer = require( './printer' )
  , Promise = require( 'promise' ); 

function defineGYP(pathJSON, cb) {

  var product = {
    'sources': []
  };
  assert( fs.existsSync( pathJSON ), "project json missing" ); 
  Printer.begin( 'define' );

  processDependencies( pathJSON ).then( function() {
    Printer.finishGreen('define');
    console.log( product );
    cb(product); 
  }); 

  function processDependencies(fileJSON) {
    
    return new Promise( function(resolve, reject) {
      fs.readFile( fileJSON, function(err, data) {
        var content;
        if (err) throw err;
        content = JSON.parse( data.toString() );
        
        if (content.hasOwnProperty('sources')) {
          content.sources.forEach(function(source, index, array) {
            product.sources = product.sources.concat(
              path.join( path.dirname(fileJSON), source ) 
            );
          });
        }

        if (  content.hasOwnProperty('import')
          &&  content.import.length) {
          content.import.forEach( function( item, index, array ) {
            processDependencies( item )
            .then( function() {
              if (index == array.length - 1) {
                resolve(); 
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
