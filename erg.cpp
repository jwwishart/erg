
// clang++ --std=c++11 erg.cpp -o bin/erg && bin/erg

#include <stdlib.h> // malloc and friendds
#include <stdio.h>  // printf 

// Generic enum generation and string mapping function.
// http://stackoverflow.com/questions/147267/easy-way-to-use-variables-of-enum-types-as-string-in-c


// TODO in case I need to change for something like a unicode string? 
//typedef char* string;

enum TokenType {
    TOKEN_UNKNOWN,

    TOKEN_WHITESPACE,

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
};

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
    int  index = 0;

    // TODO check and re-adjust capacity
    // TODO track lines and columns and index and length?
    while (*c != '\0') {
        // DEBUGGING:
        // printf("%c", *c);

        EnsureTokenArraySize(result);

        result->Tokens[index].Type = TOKEN_UNKNOWN;

        switch(*c) {
            case ' ':
                result->Tokens[index].Type = TOKEN_WHITESPACE;
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
                result->Tokens[index].Type = TOKEN_NUMBER;

                break;
            
            case '+':
                result->Tokens[index].Type = TOKEN_OPERATOR_ADD;
                break;
            case '-':
                result->Tokens[index].Type = TOKEN_OPERATOR_SUBTRACT;
                break;
            case '*':
                result->Tokens[index].Type = TOKEN_OPERATOR_MULTIPLY;
                break;
            case '/':
                result->Tokens[index].Type = TOKEN_OPERATOR_DIVIDE;
                break;
        }

        c++; // Move to next character
        index++;
        result->Length++; // Ensure the length is updated in the array
    }

    return result;
}


int main() {
    printf("Erg Compiler v0.0.1 (c) 2016 Justin Wishart\n");

    auto lexemes = lex((char *)"1 - 15 * -12");

    for (auto i = 0; i < lexemes->Length; i++) {
        PrintTokenType(lexemes->Tokens[i].Type);
        printf("\n");
    }

    // Must free tokens then the array containing them.
    free(lexemes->Tokens);
    free(lexemes);

    printf("\n");
}

