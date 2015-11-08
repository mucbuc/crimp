var assert = require( 'assert' )
  , Promise = require( 'promise' ) 
  , Printer = require( './printer' )
  , fs = require( 'graceful-fs' )
  , summary = ''
  , define = require( './definer.js' )
  , generate = require( './generator.js' )
  , build = require( './builder.js' );

process.on( 'exit', function() {
  console.log( summary );
});

function Logic(base) {

  this.define = function(jsdef, output) {
    return define( jsdef ); 
  };
  
  this.traverse = function(o) {
    return new Promise(function(resolve, reject) {
        try {
          fs.exists( o.testDir, function(exists) {
            if (exists) { 
              resolve( o ); 
            }
            else {
              throw 'invalid test definition path: ' + o.testDir;
            }
          });
        }
        catch(e)
        {
          Printer.printError( e );
          summarize( e, o );
          throw(e);
        } 
      });

  };

  this.generate = function(o) {
    return new Promise(function(resolve, reject) {

      base.makePathIfNone(o.output, function() {
        base.generate( o, function( exitCode, buildDir){
          if (!exitCode) {
            //Printer.finishGreen( o.defFile, 'generate' );
            resolve(o);
          }
          else {
            //Printer.finishRed( o.defFile ) ; 
            reject(o); 
          }
        });      
/* 
        generate( { 
          pathGYP: o.defFile, 
          testDir: o.testDir
        }, function(o) {
          resolve(o);
        } );
*/

      }); 
    });
  };

  this.build = function(o) {
    return new Promise( function(resolve, reject) {
      build( {
        'buildDir': o.output,
        'targetName': options.targetName
      }, reslove );
    });
  };

  this.run = function(o) {
    return new Promise(function(resolve, reject) {
      Printer.begin( o.defFile, 'run' );
      try {
        base.run( o, function(exitCode) {
          o['exitCode'] = exitCode;
          if (!exitCode) {
            Printer.finishGreen( o.defFile );
            resolve(o);
            summarize( " passed", o );
          }
          else {
            Printer.finishRed( o.defFile ) ; 
            reject(o);
          }
        });
      }
      catch(e) {
        Printer.printError(e);
        summarize( e, o );
        throw e;
      }
    });
  }; 
};

function summarize(e, o) {
  if (typeof e !== 'string') {
    e = e.toString();
  }
  summary += o.testDir + e + '\n';
}

module.exports = Logic;