// Copyright (c) 2016 Justin William Wishart
// Full License is found in the LICENSE.txt file

#include "../erg.h"
#include "test.h"

int main() 
{
    print_test_heading();

    #ifndef SILENT
    erg_printcwd();
    #endif

    // tokenizer_tests_1.erg
    //

    auto contents = erg_get_file_contents((const char *)"tokenizer_tests_1.erg");
    expect(strlen(contents) == 12);

// TODO(jwwishart) this SegFaults :o(
    auto tokens = lex(contents);


// UPTO HERE vvv
// TODO(jwwishart) I want to next remove the whitespace tokens
//  so that they are part of the other tokens prefix/suffix
//  so that they are accounted for but not going to bother the parser
//  yet will still be there for formatting etc...
//  There should be only 5 tokens in "1 + 22 - 456:
    // expect(tokens->Length == 5);
    expect(tokens->Length == 9);

    free(contents);
}