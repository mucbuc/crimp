#!/usr/bin/env node

var assert = require( 'assert' )
  , test = require( 'tape' )
  , define = require( '../../bin/definer' )
  , Expector = require( 'expector' ).Expector;

test( 'data prep', (t) => {
  
  var controller = new Expector(t)
  controller.expect( "data/content.json" );

  define( './test-data.json', '.', (path, cb) => {
    cb( { 
      "sources": [
        "src/main-data.cpp"
      ],
      "data": [ 
        "data/content.json" 
      ]
    } );
  } )
  .then( (gyp) => {
    controller.emit( gyp.data ).check(); 
  })
  .catch( (err) => {
    throw err;
  });
});

test( 'define recursion', (t) => {
  
  var controller = new Expector(t)
    , expected = [
      '../lib/sublib2/src/subsrc.cpp',
      '../lib/sublib/src/subsrc.h', 
      '../lib/sublib/src/subsrc.cpp'
    ];

  define( './test-import.json', '.', mapFile )
  .then( (gyp) => {
    t.assert( gyp.hasOwnProperty( 'sources' ) );
    t.deepEqual( gyp.sources, expected ); 
    t.end();
  } )
  .catch( (error) => { 
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

test( 'test definer', (t) => {
  
  var controller = new Expector(t);

  controller.expect( '["../src/main.cpp"]' );
  define( './test.json', '.', (path, cb) => {
    if (path == "lib/crimp/def.json")
      cb( {} );
    else 
    cb( { "sources": [ "src/main.cpp" ] } );
  } )
  .then( (product) => {
    t.assert( product.hasOwnProperty('sources') );
    
    console.log( JSON.stringify(product.sources) ); 
    controller.emit( JSON.stringify(product.sources) ).check();
  });
});

test( 'test pass thru', (t) => {
  var controller = new Expector(t);
  controller.expect( 'rand_val' );
  define( './rand_prop.json', '.', (path, cb) => {
    cb( { "rand_prop": "rand_val" } );
  })
  .then( (product) => {
    t.assert( product.hasOwnProperty('rand_prop') );
    controller.emit( product.rand_prop ).check();
  });
});

test( 'test property merge', (t) => {
  var controller = new Expector(t);
  
  controller.expect( 'c' );

  define( './base.json', '.', (path, cb) => {
    if (path == 'a.json')
      cb( { a: 'b' } );
    if (path == 'b.json')
      cb( { a: 'c' } );
    if (path == 'base.json')
      cb( { import: [ 'a.json', 'b.json' ] } );
  })
  .then( (product) => {
    t.assert( product.hasOwnProperty( 'a' ) ); 
    controller.emit( product.a ).check();
  });

});

