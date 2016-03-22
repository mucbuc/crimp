var ansi = require( 'ansi' )
  , cursor = ansi( process.stdout )
  , summary = '';

var Printer = {

	cursor: cursor, 

	begin: ( msg1, msg2 ) => {
		cursor.green();
		process.stdout.write( msg1 + ': ' );
		cursor.reset();
		console.log( msg2 );
		console.time( msg1 );
	}, 

	finishGreen: ( msg1 ) => {
		cursor.green();
		console.timeEnd( msg1 );
		cursor.reset();
	}, 

	finishRed: ( msg1 ) => {
		cursor.red();
		console.timeEnd( msg1 );
		cursor.reset();
	}, 

	printError: ( msg ) => {
		cursor.red(); 
		console.log( msg ); 
		cursor.reset();
	}
};

module.exports = Printer;