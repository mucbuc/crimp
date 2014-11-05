#!/usr/bin/env node

var assert = require( 'assert' )
  , events = require( 'events' )
  , cp = require( 'child_process' )
  , emitter = new events.EventEmitter()
  , Reader = require( './Reader' );

emitter.on( 'addSubtree', function( dependency, name ) {
	
	var child = cp.spawn( 'git', [
			'subtree',
			'add', 
			'-P',
			name, 
			name,
			'master', 
			'--squash'
		], {
				stdio: 'inherit'
			}); 

});

installDependencies( Reader.readDependencies() );

function installDependencies( dependencies, index ) {
	
	if (typeof index === 'undefined')
		index = 0;

	if (index < dependencies.length)
	{
		var child
		  , dependency = dependencies[ index ]
		  , name = Reader.libName( dependency );

		child = cp.spawn( 'git', [ 
				'remote',
				'add',
				'-f',
				name,
				dependency,
			], {
				stdio: 'inherit'
			} );

		child.on( 'exit', function( code ) {
			installDependencies( dependencies, index + 1 );
			if (!code) {
				console.log( 'installed: ', name );
				emitter.emit( 'addSubtree', dependency, name );
			}
			else { 
				console.log( 'install failed: ', name );
			}
		});
	} 
}