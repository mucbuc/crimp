#!/usr/bin/env node
require( 'child_process' )
.fork( './plank/bin/test.js', [ '-p', 'test/def/' ] );