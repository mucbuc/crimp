var assert = require( 'assert' )
  , jsoncpp = require( 'jsoncpp' ).translateFile
  , fs = require( 'fs.extra' )
  , path = require( 'path' ); 

assert( typeof jsoncpp !== 'undefined' );

module.exports = function(pathIn, cb) {
  
  jsoncpp( pathIn, function(result) {

    var pathOut = path.join( path.dirname(pathIn), '..', 'src', 'data' );

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