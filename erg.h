// Copyright (c) 2016 Justin William Wishart
// Full License is found in the LICENSE.txt file

#include <stdlib.h> // malloc and friends
#include <stdio.h>  // printf
#include <string.h> // strlen, strcpy

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
