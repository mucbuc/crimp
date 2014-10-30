#include <iostream>

#include "test.h"
#include "fluke_test.h"

#include <lib/ohm/src/quemitter.h>


int main(int argc, const char * argv[])
{
    check_lexer();
    check_parser();
    return 0;
}

