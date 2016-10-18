// Copyright (c) 2016 Justin William Wishart
// Full License is found in the LICENSE.txt file

#include <chrono>   // high_resolution_clock
#include <stdio.h>  // printf
#include <assert.h> // assert
#include <stdlib.h> // malloc and friends
#include <string.h> // strlen, strcpy

#include "util.h"
#include "os.h"
#include "compiler_arguments.h"
#include "string_builder.h"

enum TokenType 
{
    TOKEN_UNKNOWN,

    TOKEN_WHITESPACE,
    TOKEN_NEWLINE,

    TOKEN_NUMBER,

    TOKEN_OPERATOR_ADD,
    TOKEN_OPERATOR_SUBTRACT,
    TOKEN_OPERATOR_MULTIPLY,
    TOKEN_OPERATOR_DIVIDE,
};

struct Token 
{
    TokenType Type;

    // Location Metadata
    int Index;
    int Line;
    int Column;
    int Length;

    char * Raw;
    char * PrefixedWhitespace;
    char * SuffixedWhitespace;
};

// TODO create macro for creation of arrays for given types which have the 
// ensure_token_array_size() or Ensure***ArraySize() 
struct TokenArray 
{
    int    Length;
    int    Capacity;

    Token *Tokens;
};

#ifdef DEBUG 
    #include "compiler_debug.h"
#endif

// TODO cleanup
// TODO extra checks
void ensure_token_array_size(TokenArray *array) {
    if (array->Length >= array->Capacity) {
        auto currentCapacity = array->Capacity;
        auto newCapacity     = array->Capacity * 2;

        array->Tokens = (Token*)realloc(array->Tokens, sizeof(Token) * newCapacity);

        array->Capacity = newCapacity;
    }
}

TokenArray *lex(char *code) {
    assert(code != NULL);

    auto result = (TokenArray *)malloc(sizeof(TokenArray));
    result->Length   = 0;
    result->Capacity = 4;
    result->Tokens = (Token*)malloc(sizeof(Token) * 4);

    char *c = code;
// TODO FIX THIS NEXT LINES ISSUES ITS UNCLEAR ETC
    int  tokenIndex = 0; // TODO THIS IS USED FOR INDEX INTO TOKENS AND OTHHER THINGS FIX THIS!!!!!!
    int  line = 1;
    int  column = 1;

    // TODO check and re-adjust capacity
    // TODO track lines and columns and index and length?
    while (*c != '\0') {
        // DEBUGGING:
        // printf("%c", *c);

        ensure_token_array_size(result);

        auto token = &result->Tokens[tokenIndex];

        token->Type   = TOKEN_UNKNOWN;
        token->Index  = tokenIndex;
        token->Line   = line;
        token->Column = column;
        token->Length = 1;

        switch (*c) {
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
            {
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
            }
            case ' ':
            case '\t':
            {
                token->Type = TOKEN_WHITESPACE;
                break;
            }
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
            {
                token->Type = TOKEN_NUMBER;
                token->Raw = (char *)calloc(16, sizeof(char)); // zero so we can just add numbers...
                token->Raw[0] = *c;

                auto index = 1;
                auto found = false;

                do {
                    c++; // move past the current character...

                    switch (*c) {
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
                            token->Raw[index] = *c;
                            index++;

                            column++;
                            break;
                        default:
                            c--; // move back as this character is not part of the numer
                            found = true;
                            break;
                    }
                } while(*c != '\0' && !found);

                break;
            }
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
        tokenIndex++;
        result->Length = tokenIndex;
    }

    return result;
}


/*
    Compiler Execution Duration Printing Functionality
*/

#include <chrono>
typedef std::chrono::system_clock::time_point TimePoint;

TimePoint timer_now() 
{
    return std::chrono::high_resolution_clock::now();
}

void print_compiler_execution_time(TimePoint start, TimePoint end) 
{
    auto total = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

    auto microseconds = total % 1000;
    total /= 1000;

    auto milliseconds = total % 1000;
    total /= 1000;

    auto seconds = total % 60;
    total /= 60;

    auto minutes = total % 60;
    total /= 60;

    auto hours = total % 24;
    total /= 24;

    auto days = total;

    if (days >= 1) {
        printf("%ld day", days);
        if (days > 1) printf("s");
        printf(" ");
    }
    if (hours >= 1) {
        printf("%ld hour", hours);
        if (hours > 1) printf("s");
        printf(" ");
    }
    if (minutes >= 1) {
        printf("%ld minute", minutes);
        if (minutes > 1) printf("s");
        printf(" ");
    }
    if (seconds >= 1) {
        printf("%ld second", seconds);
        if (seconds > 1) printf("s");
        printf(" ");
    }
    if (milliseconds >= 1) {
        printf("%ld millisecond", milliseconds);
        if (milliseconds > 1) printf("s");
        printf(" ");
    }
    if (microseconds >= 1) {
        printf("%ld microsecond", microseconds);
        if (microseconds > 1) printf("s");
    }
}

