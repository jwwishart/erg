// Copyright (c) 2016 Justin William Wishart
// Full License is found in the LICENSE.txt file

#include <chrono>
#include "erg.h"

int main(int argc, char *argv[]) {
    auto start = std::chrono::high_resolution_clock::now();

    CompilerArgumentFlags flags;
    parse_flags(argc, argv, &flags);

    if (!flags.enableSilentMode) 
    {
        printf("Erg Compiler v0.0.1 (c) 2016 Justin Wishart\n");
    }

    auto lexemes = lex((char *)"1 + 22 -456");
    // NEWLINES auto lexemes = lex((char *)"1 \n\r \t 2 \n 3 \r\r 4 \n\n 5 \r\r");

    // TODO should just put all this into a single function which just returns... I will
    // do this when I dump more things I think
    #ifdef DEBUG 
        printf("WARNING: erg compiler build with debugging enabled\n");
        print_token_array(lexemes);
    #endif

    free(lexemes->Tokens);
    free(lexemes);

    // Print Execution Time
    auto end = std::chrono::high_resolution_clock::now();

    if (!flags.enableSilentMode) 
    {
        printf("Time: ");
        print_compiler_execution_time(start, end);
        printf("\n");
    }
}

