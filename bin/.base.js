var events = require( 'events' );

exports.Processor = require( 'mucbuc-jsthree' ).Processor;
exports.makeEmitter = makeEmitter;

function makeEmitter() 
{
	var e = new events.EventEmitter();
	e.on( 'stdout', print );
	e.on( 'stderr', print );

	function print(data) {
		process.stdout.write( data.toString() ); 
	}
	return e;
}


