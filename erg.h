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


// TODO pull these string thingies out into util.h I think...
char * allocate_character_array() 
{
    auto lengthAndCap = sizeof(int) * 2;
    auto result = (char *)calloc(sizeof(char) * 16 + lengthAndCap, sizeof(char));
    auto start = result - lengthAndCap;

    auto location = (int *)(start);
    *location = 0;
    location = (int *)(start) + 1;
    *location = 16; 

    return result;
}

// TODO debug only?
void dump_character_array(char * str) {
    auto lengthAndCap = sizeof(int) * 2;

    printf("Value: %s\n", str);

    str -= lengthAndCap;

    printf("Length: %d\n", (*(int *)str));
    printf("Capacity: %d\n", (*(((int *)str)+1)));
}

void free_character_array(char * string) {
    auto lengthAndCap = sizeof(int) * 2;
    string -= lengthAndCap;
    free(string);
}

char * append_character_array(char * str, char * append) {
    auto lengthAndCap = sizeof(int) * 2;
    auto lengthOfAppend = strlen(append);

    int capacity = (*(((int *)str)+1));
    int length   = (*(int *)str);

// UPTO HERE vvv
    // TODO reallocate when capacity reached or going over...

    // TODO errors
    strcpy(str + lengthOfAppend, append);

    length += lengthOfAppend;

    // Set the new length
    auto start = str - lengthAndCap;
    auto location = (int *)(start);
    *location = length;

    return str;
}

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
