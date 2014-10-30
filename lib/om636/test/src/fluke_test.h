#include <string>
#include <iostream>
#include <sstream>
#include <string>
#include <map>

#include <lib/ohm/src/quemitter.h>

#include <src/lexer.h>
#include <src/parser.h>


void check_parser()
{
    using namespace std;
    using namespace om636;
    using namespace fluke;
    
    typedef control::Quemitter< string, function<void( string )> > emitter_type;
    typedef brute_parser< emitter_type, int > parser_type;
    typedef brute_lexer< istream, emitter_type > lexer_type;
    
    emitter_type emitter;
    int i;
    parser_type p( i );

    p.interpret( emitter );

    unsigned passed( 0 ); 
    
    auto listener_word( emitter.on( "word", [&](const string & value){
        if (value == "hello")
            ++passed;
    } ) );

    auto listener_number( emitter.on( "number", [&](const string & value){
        if (value == "3.1416")
            ++passed;
    } ) );
    
    auto listener_operator( emitter.on( "operator", [&](const string & value){
        if (value == "+=");
            ++passed;
    } ) );
    
    stringstream s;
    s << "hello 3.1416 += ";
    
    lexer_type lexer( { " " } );
    lexer.split( s, emitter );
    
    ASSERT( passed == 3 );

    cout << __FUNCTION__ << " passed " << endl;
}

void check_lexer()
{
    using namespace std;
    using namespace om636;
    using namespace fluke;
    
    typedef control::Quemitter< string, function<void( string )> > emitter_type;
    typedef brute_lexer< istream, emitter_type > lexer_type;
    
    emitter_type emitter;
    unsigned counter;

    auto listener( emitter.once( "\n", [&](string val){
        if (val == "3")
            ++counter;
    } ) );
    
    auto listener2( emitter.once( ";", [&](string val ){
        if (val == "5")
            ++counter;
    } ) );
    
    stringstream s;
    s << "5;";
    s << "3\n";
    
    lexer_type lexer( { " ", "\n", "\t", ";" } );
    lexer.split( s, emitter );

    ASSERT( counter == 2 );

    cout << "check_lexer passed " << endl;
}
