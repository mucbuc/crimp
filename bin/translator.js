var assert = require( 'assert' )
  , jsoncpp = require( 'jsoncpp' ).translateFile
  , fs = require( 'fs.extra' ); 

assert( typeof jsoncpp !== 'undefined' );

module.exports = function(pathIn, pathOut, cb) {

  assert( typeof pathIn !== 'undefined' );
  assert( typeof pathOut !== 'undefined' );
  
  jsoncpp( pathIn, function(result) {
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