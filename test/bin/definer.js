#!/usr/bin/env node

var assert = require( 'assert' )
  , test = require( 'tape' )
  , define = require( '../../bin/definer' )
  , Expector = require( 'expector' ).Expector;

test( 'data prep', function(t) {
  
  var controller = new Expector(t)
  controller.expect( "data/content.json" );

  define( './test-data.json', '.', function(path, cb) {
    cb( { 
      "sources": [
        "src/main-data.cpp"
      ],
      "data": [ 
        "data/content.json" 
      ]
    } );
  } )
  .then( function(gyp) {
    controller.emit( gyp.data ).check(); 
  })
  .catch( function(err) {
    throw err;
  });
});

test.only( 'define recursion', function(t) {
  
  var controller = new Expector(t)
    , expected = [
      '../lib/sublib2/src/subsrc.cpp',
      '../lib/sublib/src/subsrc.h', 
      '../lib/sublib/src/subsrc.cpp'
    ];

  define( './test-import.json', '.', mapFile )
  .then( function(gyp) {
    t.assert( gyp.hasOwnProperty( 'sources' ) );
    t.deepEqual( gyp.sources, expected ); 
    t.end();
  } )
  .catch( function(error) { 
  
    console.log( error ); 
  });

  function mapFile(path, cb) {

    var result = {
      "test-import.json": 
        { import: [ 'lib/sublib/def.json' ] },
      "lib/sublib/def.json": 
        { import: [ 'lib/sublib2/def.json' ],
          sources: [ 'src/subsrc.h', 'src/subsrc.cpp' ] },
      "lib/sublib2/def.json": 
        { sources: [ 'src/subsrc.cpp' ] }
      };

    assert( result.hasOwnProperty( path ) ); 

    cb( result[path] ); 
  }
});

test( 'test definer', function(t) {
  
  var controller = new Expector(t);

  controller.expect( '["../src/main.cpp"]' );
  define( './test.json', '.', function(path, cb) {
    if (path == "lib/crimp/def.json")
      cb( {} );
    else 
    cb( { "sources": [ "src/main.cpp" ] } );
  } )
  .then( function(product) {
    t.assert( product.hasOwnProperty('sources') );
    
    console.log( JSON.stringify(product.sources) ); 
    controller.emit( JSON.stringify(product.sources) ).check();
  });
});