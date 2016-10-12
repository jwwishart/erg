// Copyright (c) 2016 Justin William Wishart
// Full License is found in the LICENSE.txt file

#include <chrono>
#include "erg.h"

int main(int argc, char *argv[]) {
    // Start Timer
    auto start = std::chrono::high_resolution_clock::now();

    // Parse Arguments
    CompilerArgumentFlags flags;
    parse_flags(argc, argv, &flags);

    // Welcome Message
    if (!flags.enableSilentMode) {
        printf("Erg Compiler v0.0.1 (c) 2016 Justin Wishart\n");
    }

    auto lexemes = lex((char *)"1 + 22 -456");
    // NEWLINES auto lexemes = lex((char *)"1 \n\r \t 2 \n 3 \r\r 4 \n\n 5 \r\r");

// TODO should just put all this into a single function which just returns... I will
// do this when I dump more things I think
#ifdef DEBUG 
    printf("*** Compiler Debugging Enabled ***");
    printf("\n");

    print_token_array(lexemes);
#endif

    // Must free tokens then the array containing them.
    free(lexemes->Tokens);
    free(lexemes);


    // Calculate Compilation Time
    //  chrono doesn't seem to have the functionality?
    auto end = std::chrono::high_resolution_clock::now();

    auto delta = end - start;

    // nanoseconds = 1 billionth of a second
    auto nanoseconds = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();

    // microseconds = 1 millionth of a second
    auto microseconds = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    // milliseconds = 1 thousandth of a second
    auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();

    // seconds
    auto seconds = std::chrono::duration_cast<std::chrono::seconds>(end - start).count();

    // minutes
    auto minutes = std::chrono::duration_cast<std::chrono::minutes>(end - start).count();

    // TODO(jwwishart) how can I get around minutes but get remainer duration
    //  and count in the next lowest unit?
    //  ex: 1 hour 12 mins 13 seconds 987 milliseconds?
    /*
        - maybe I can just divide the high_resolution_clock::now() result
          as it should just be storing nanoseconds... 
    */
    printf("Time: %ld minutes\n", minutes);
}

