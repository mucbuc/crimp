var assert = require( 'assert' )
  , jsoncpp = require( 'jsoncpp' ).translateFile
  , fs = require( 'fs' )
  , path = require( 'path' );

assert( typeof jsoncpp !== 'undefined' );

module.exports = function(pathIn, cb) {
  
  jsoncpp( pathIn, function(result) {

    var pathOut = path.join( 
          path.dirname(pathIn), 
          '..',
          'src',
          'data',
          path.basename(path.basename(pathIn) ) );

    fs.writeFile( pathOut + '.h', result, function(err) {
      if (err) throw err;
      if (typeof cb === 'function') {
        cb();
      }
    } );
  });
};