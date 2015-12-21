var assert = require( 'assert' )
  , jsoncpp = require( 'jsoncpp' )
  , fs = require( 'fs' )
  , path = require( 'path' );

assert( typeof jsoncpp !== 'undefined' );

module.exports = function(pathIn) {

	jsoncpp( pathIn, function(result) {

		console.log( result ); 
		var pathOut = path.join( 
					path.dirname(pathIn), 
					'..',
					'src',
					'data',
					path.basename(path.basename(pathIn) ) );

		fs.writeFile( pathOut + '.h', result, function(err) {
			console.log( err );
		} );
	});
};