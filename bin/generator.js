var assert = require( 'assert' )
  , path = require( 'path' );

function generate( context ) {

  assert( context.hasOwnProperty( 'testDir' ) );
  assert( context.hasOwnProperty( 'pathGYP' ) );
  assert( context.hasOwnProperty( 'tempDir' ) );

  return new Promise( (resolve, reject) => {
    var args = [
          '--depth=.',
          'host.gyp'//context.nameGYP
        ];  
   
    console.log( 'cprocess.cwd()', process.cwd() );

    context
    .spawn( 'gyp', args, '.', resolve, reject )
    .on( 'error', (error) => {
      console.log( error ); 
    });
  });
}

module.exports = generate;
