
// RELEASE:
// TODO optimizations etc all turned on
// clang++ --std=c++11 erg.cpp -o bin/erg
// clang++ --std=c++11 erg.cpp -o bin/erg && bin/erg

// DEBUG:
// clang++ --std=c++11 -g -D DEBUG erg.cpp -o bin/erg
// clang++ --std=c++11 -g -D DEBUG erg.cpp -o bin/erg && bin/erg

/*

    - Lexer
        x Lex Some More Characters (newlines and tabs)
        x Line, Column, Index information in token
        - Create Lexer Test Strings File (not 1.erg etc... remove them)
        - Lex full numbers
        - Lex Strings
        - Lex decimal numbers?
        - Comments
            - Single Line Comments (# or //?)
            - Nested Comments
        - Length of
            - Number Literals
            - String Literals
            - Identifiers
            - etc
        - Lexer Dump File (.lex)

    - Parser
        - Create AST Node

    - Performance
        - Optimize data structure alignment
    
    - Testing Framework
        - Tests should be in code
        - Code to run through the compiler ought to be stored in files not 
          in the c++ code as strings etc.
        - Should provide an easy way to load the appropriate test by use of
          the number only
        - The Code should verify the results
        - The compiler results ought to be appropriately structured so that
          a test could analyse the result object to find
            - errors
            - warnings
            - anomolies in tokens, or ast that it is expecting to find et
            - should show success/failure for parsing
            - should allow access to bytecode etc
            - EVERYTHING that a test would need to verify behaviour 

    - Other
        - Get rid of the debugging output behind a flag instead of compile time
          directive... dump to files in another directory to keep the output 
          nice and clean!
        - Testing mechanims
            - tests folder includes bunch of files all parsed and compared with
              an expected output file (json maybe?) containing meta about
              the expected results of the parsing of the file(compilation)
            - need to have compiler flag --run-compiler-tests
            - essentially system tests that run to test compilation of certain
              structures of code: empty file, simple expressions(?) etc... should
              be verifiable somehow??? maybe the compiler needs to output a json
              file containing tokens, ast etc? errors, warnings and ought to be
              able to say: this should warn, so find a warning of type W1424 which is
              a warning that "bla" which should show with this sort of code... etc...
        - Shell scripts to build_debug and build_release... should execute
          required clang commandlines with the required -D DEBUG symbol for 
          debug, as well as including other optimizations etc...
          
          Maybe we should have the following scripts
          - debug - builds and executes GDB, all additional arguments are forwarded
            to the executable
          - build - builds. Can take debug|release as argument, default is debug
            all additional arguments are passed to the executable
          - run   - builds in debug mode and executes,
            all additional arguments are passed to the executable
          - test  - runs compiler tests (build in debug and --run-compiler-tests
            passed to the compiler

        - Create way to generate enum and string value mapping or function
          to return a string representation of the enum to avoid duplication

 */

// TODO remove below stuff?
// WARNING use "-D DEBUG" argument to clang++ instead of below... 
//#define DEBUG

#include <stdlib.h> // malloc and friendds
#include <stdio.h>  // printf
#include "compiler_arguments.h"

#ifdef DEBUG 
    #include "compiler_debug.h"
#endif

// Generic enum generation and string mapping function.
// http://stackoverflow.com/questions/147267/easy-way-to-use-variables-of-enum-types-as-string-in-c


// TODO in case I need to change for something like a unicode string? 
//typedef char* string;

enum TokenType {
    TOKEN_UNKNOWN,

    TOKEN_WHITESPACE,
    TOKEN_NEWLINE,

    TOKEN_NUMBER,

    TOKEN_OPERATOR_ADD,
    TOKEN_OPERATOR_SUBTRACT,
    TOKEN_OPERATOR_MULTIPLY,
    TOKEN_OPERATOR_DIVIDE,
};

void PrintTokenType(TokenType type) {
    switch(type) {
        case TOKEN_UNKNOWN:
            printf("TOKEN_UNKNOWN");
            return;

        case TOKEN_WHITESPACE:
            printf("TOKEN_WHITESPACE");
            return;
        case TOKEN_NEWLINE:
            printf("TOKEN_NEWLINE");
            return;
            

        case TOKEN_NUMBER:
            printf("TOKEN_NUMBER");
            return;

        case TOKEN_OPERATOR_ADD:
            printf("TOKEN_OPERATOR_ADD");
            return;
        case TOKEN_OPERATOR_SUBTRACT:
            printf("TOKEN_OPERATOR_SUBTRACT");
            return;
        case TOKEN_OPERATOR_MULTIPLY:
            printf("TOKEN_OPERATOR_MULTIPLY");
            return;
        case TOKEN_OPERATOR_DIVIDE:
            printf("TOKEN_OPERATOR_DIVIDE");
            return;
    }

    printf("*** Unsupported Token Type given to PrintTokenType() ***");
}



struct Token {
    TokenType Type;

    // Location Metadata
    int Index;
    int Line;
    int Column;
    int Length;
};


void PrintToken(Token * token) {
    printf("(L%d:C%d:Len%d) > ",  token->Line, token->Column, token->Length);

    PrintTokenType(token->Type);
}


// TODO create macro for creation of arrays for given types which have the EnsureTokenArraySize() or Ensure***ArraySize() 
struct TokenArray {
    int    Length;
    int    Capacity;

    Token *Tokens;
};


// TODO cleanup
// TODO extra checks
void EnsureTokenArraySize(TokenArray *array) {
    if (array->Length >= array->Capacity) {
        auto currentCapacity = array->Capacity;
        auto newCapacity     = array->Capacity * 2;

        array->Tokens = (Token*)realloc(array->Tokens, sizeof(Token) * newCapacity);

        array->Capacity = newCapacity;
    }
}


// TODO 
TokenArray *lex(char *code) {
    auto result = (TokenArray *)malloc(sizeof(TokenArray));
    result->Length   = 0;
    result->Capacity = 4;
    result->Tokens = (Token*)malloc(sizeof(Token) * 4);

    char *c = code;
// TODO FIX THIS NEXT LINES ISSUES ITS UNCLEAR ETC
    int  index = 0; // TODO THIS IS USED FOR INDEX INTO TOKENS AND OTHHER THINGS FIX THIS!!!!!!
    int  line = 1;
    int  column = 1;

    // TODO check and re-adjust capacity
    // TODO track lines and columns and index and length?
    while (*c != '\0') {
        // DEBUGGING:
        // printf("%c", *c);

        EnsureTokenArraySize(result);

        auto token = &result->Tokens[index];

        token->Type   = TOKEN_UNKNOWN;
        token->Index  = index;
        token->Line   = line;
        token->Column = column;
        token->Length = 1;

        switch(*c) {
            // Newline Information
            // - Windows \n\r
            // - Max:    \r
            // - Linux   \n
            // Approach:
            //  if \n comes with an \r after it normalize to just \n
            //  if \r is present the replace it with an \n
            // i.e. normalize to a single \n for all code sources.
            case '\n':
            case '\r':
                token->Type = TOKEN_NEWLINE;
                
                // Handle Mac \r, just continue
                if (*c == '\r') {
                    line++;
                    column = 1;
                    break;
                }

                // Handle Windows \n\r combination, skip additional character.
                // TODO the \0 check is redundant? must be zero terminated anyway???
                //  so can I just safely remove it?... I don't see why not? leave till
                //  clearer brain available :o)
                if (*c == '\n' && *(c + 1) != '\0' && *(c + 1) == '\r') {
                    line++;
                    column = 1;
                    token->Length = 2;
                    c++; // skip the \r characer

                    break;
                }

                // Handle Linux \n
                if (*c == '\n') {
                    line++;
                    column = 1;
                    break;
                }

                // NOTE this ought be impossible... But if ever a regression
                //  happens then this will hopefully make it clear it happened :o)
                token->Type = TOKEN_UNKNOWN;
                break;
                
            case ' ':
            case '\t':
                token->Type = TOKEN_WHITESPACE;
                break;

            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                token->Type = TOKEN_NUMBER;
                
                // UPTO THIS
                // do {
                //     c++;

                //     switch(*c) {
                //         case '0':
                //         case '1':
                //         case '2':
                //         case '3':
                //         case '4':
                //         case '5':
                //         case '6':
                //         case '7':
                //         case '8':
                //         case '9':
                //             column++;
                //         default:
                //             c--; // move back as this character is not part of the numer
                //             break;
                //     }
                // } while(*c != '\0');

                break;
            case '+':
                token->Type = TOKEN_OPERATOR_ADD;
                break;
            case '-':
                token->Type = TOKEN_OPERATOR_SUBTRACT;
                break;
            case '*':
                token->Type = TOKEN_OPERATOR_MULTIPLY;
                break;
            case '/':
                token->Type = TOKEN_OPERATOR_DIVIDE;
                break;
        }

        // Set Token Location Information

        // Move everything ready for next token
        // TODO this is the same as the newline handling windows newline section!!!
        column++;
        c++; // Move to next character
        index++;
        // TODO: why not just figure this out from the index at the end?
        result->Length++; // Ensure the length is updated in the array
    }

    return result;
}

int main(int argc, char *argv[]) {
    // Parse Arguments
    CompilerArgumentFlags flags;
    parseFlags(argc, argv, &flags);

    if (!flags.enableSilentMode) {
        printf("Erg Compiler v0.0.1 (c) 2016 Justin Wishart\n");
    }

    auto lexemes = lex((char *)"1 + 12");
    // NEWLINES auto lexemes = lex((char *)"1 \n\r \t 2 \n 3 \r\r 4 \n\n 5 \r\r");

#ifdef DEBUG 
    printf("*** Compiler Debugging Enabled ***");
    printf("\n");

    for (auto i = 0; i < lexemes->Length; i++) {
        PrintToken(&lexemes->Tokens[i]);
        
        printf("\n");
    }
#endif

    // Must free tokens then the array containing them.
    free(lexemes->Tokens);
    free(lexemes);

    //printf("\n");
}

