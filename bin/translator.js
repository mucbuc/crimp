var assert = require( 'assert' )
  , jsoncpp = require( 'jsoncpp' ).translateFile
  , fs = require( 'fs' )
  , path = require( 'path' )
  , mr = require( 'mkdir-recursive' ); 

assert( typeof jsoncpp !== 'undefined' );

module.exports = function(pathIn, cb) {
  
  jsoncpp( pathIn, function(result) {

    var pathOut = path.join( path.dirname(pathIn), '..', 'src', 'data' );

    mr.mkdir(pathOut, function(err) {
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