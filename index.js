var program = require( 'commander' );

program
	.version( '0.0.1' )
	.option( '-b , --batch [path]', 'execute on batch')
	.option( '-d , --debug', 'build debug target' )
	.option( '-r , --release', 'build release target' )
	.option( '-t , --test', 'build test target and run (default)' );
	
module.exports = require( './bin/test.js' );