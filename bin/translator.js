var assert = require( 'assert' )
  , translateFile = require( 'jsoncpp' ).translateFile
  , fs = require( 'fs' ); 

assert( typeof translateFile !== 'undefined' );

module.exports = function(pathIn, pathOut, cb) {

  assert( typeof pathIn !== 'undefined' );
  assert( typeof pathOut !== 'undefined' );
  
  translateFile( pathIn, function(result) {
    fs.writeFile( 
      pathOut, 
      result, 
      function(err) {
        if (err) throw err;
        if (typeof cb === 'function') {
          cb();
        }
      }); 
    });
};