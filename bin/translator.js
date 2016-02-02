var assert = require( 'assert' )
  , jsoncpp = require( 'jsoncpp' ).translateFile
  , fs = require( 'fs.extra' )
  , path = require( 'path' ); 

assert( typeof jsoncpp !== 'undefined' );

module.exports = function(pathIn, pathOut, cb) {

  assert( typeof pathIn !== 'undefined' );
  assert( typeof pathOut !== 'undefined' );
  
  jsoncpp( pathIn, function(result) {
    fs.mkdirp(pathOut, function(err) {
      if (err) throw err;
      fs.writeFile( 
        path.join( pathOut, path.basename(path.basename(pathIn) ) + '.h' ), 
        result, 
        function(err) {
          if (err) throw err;
          if (typeof cb === 'function') {
            cb();
          }
        } ); 
    });
  });
};