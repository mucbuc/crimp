#!/usr/bin/env node

var assert = require( 'assert' )
  , events = require( 'events' )
  , path = require( 'path' )
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
		  , name = libName( dependency );

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
			if (!code) {
				installDependencies( dependencies, index + 1 ); 

				emitter.emit( 'addSubtree', dependency, name );
			}
		});

		function libName( dependency ) {
			return 'lib/' + path.basename( dependency, '.git' ); 
		}
	} 
}