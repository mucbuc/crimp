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
    cb(product); 
  }); 

  function processDependencies(pathJSON) {
    
    return new Promise( function(resolve, reject) {
      fs.readFile( pathJSON, function(err, data) {
        var content;
        if (err) throw err;
        content = JSON.parse( data.toString() );
        
        if (content.hasOwnProperty('sources')) {
          product.sources = product.sources.concat( content.sources );
        }

        if (  content.hasOwnProperty('import')
          &&  content.import.length) {
          content.import.forEach( function( item, index, array ) {
            var importPath = path.join( path.dirname(pathJSON), item); 
            processDependencies( importPath )
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
