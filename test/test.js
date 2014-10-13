#!/usr/bin/env node

var assert = require( 'assert' )
  , cp = require( 'child_process' )
  , events = require( 'events' )
  , path = require( 'path' )
  , fs = require( 'graceful-fs' )
  , emitter = new events.EventEmitter
  , util = require( 'util' )
  , gr = require( 'gyp-reader' )
  , ansi = require( 'ansi' )
  , cursor = ansi( process.stdout )
  , program = require( 'commander' );

assert( typeof cp !== 'undefined' );


program
	.version( '0.0.0' )
	.option( '-p, --path [path]', 'test path' )
	.parse( process.argv );

if (!program.path) {
	program.path = __dirname;
}

attachLogic( emitter );

emitter.emit( 'traverse', program.path );

function attachLogic(emitter) {

	emitter.on( 'run', function( defFile, testDir ) {
		begin( defFile, 'run' );
		run( defFile, testDir, function(exitCode) {
			if (!exitCode) {
				finishGreen( defFile );
				console.log( 'test passed' );
			}
			else {
				finishRed( defFile ) ; 
				console.log( 'failed with exit code: ', exitCode );
			}
		});
	}); 

	emitter.on( 'build', function( defFile, testDir ) {
		begin( defFile, 'build' );
		build( defFile, testDir, function( exitCode ) { 
			finishGreen( defFile );
			if (!exitCode) {
				emitter.emit( 'run', defFile, testDir );
			}
		});
	});

	emitter.on( 'generate', function( defFile, testDir ) {
		begin( defFile, 'generate' );
		generate( defFile, testDir, function( exitCode ){
			finishGreen( defFile, 'generate' );
			if (!exitCode) {
				emitter.emit( 'build', defFile, testDir );
			}
		});
	});

	emitter.on( 'traverse', function(testDir) {
		traverse( testDir, function(gypFile) {
			emitter.emit( 'generate', gypFile, testDir );
		});
	});

	function begin( msg1, msg2 ) {
		cursor.green();
		process.stdout.write( msg1 + ': ' );
		cursor.reset();
		console.log( msg2 );
		console.time( msg1 );
	}

	function finishGreen( msg1 ) {
		cursor.green();
		console.timeEnd( msg1 );
		cursor.reset();
	}

	function finishRed( msg1 ) {
		cursor.red();
		console.timeEnd( msg1 );
		cursor.reset();
	}

	function traverse( testDir, cb ) {
		fs.readdir( testDir, function( err, files ) {
				files.forEach( function( file ) {
					if (path.extname(file) == '.gyp') {
						cb( file ); 
					}
				} );	
			} );
	}

	function generate( defFile, testDir, cb ) {
		cp.spawn( 
			'gyp', 
			[
				path.join( testDir, defFile ),
				'--depth==0', 
				'--generator-output=build'
		  ])
		.on( 'close', function( code ) {
			cb( code );
		} );
	}

	function build( defFile, testDir, cb ) {
		var defName = path.basename( defFile, '.gyp' );
		cp.spawn( 
			'xcodebuild', 
			[
				"-project",
				defName + '.xcodeproj'
			], {
			cwd: path.join( testDir, 'build' )
		} )
		.on( 'close', function( code ) {
			cb( code ); 
		} );
	}

	function run( defFile, testDir, cb ) {
		gr( path.join( testDir, defFile ), function( err, data ) {
				if (err) {
					cursor.red();
					process.stdout.write( defFile + ': ' );
					cursor.reset();
					console.log( err );
				}
				else {
					data.targets.forEach( function( target ) {
						exec( target.target_name, cb );
					} );
				}
			} );

		function exec(target, cb) {
			cp.spawn( 
				path.join( testDir, 'build/Default', target ), 
				[], {
				stdio: 'pipe'
			})
			.on( 'close', function( code ) {
				cb( code );
			})
			.stdout.on( 'data', function( data ) {
				cursor.blue();
				process.stdout.write( target + ': ' ); 
				cursor.reset();
				console.log( data.toString() );
			});
		}
	}
}
