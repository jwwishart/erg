#include <stdio.h>
#include <cstdlib>

// Generic enum generation and string mapping function.
// http://stackoverflow.com/questions/147267/easy-way-to-use-variables-of-enum-types-as-string-in-c


// TODO in case I need to change for something like a unicode string? 
//typedef char* string;

enum TokenType {
    TOKEN_UNKNOWN,

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

struct TokenArray {
    int    Length;
    int    Capacity;
    Token *Tokens;
};

void EnsureTokenArraySize(TokenArray *array) {
    if (array->Length == array->Capacity) {
        auto currentCapacity = array->Capacity;
        auto newCapacity = array->Capacity * 2;
        
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

        result->Tokens[index].Type = TOKEN_UNKNOWN;

        switch(*c) {
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
                goto done;
            
            case '+':
                result->Tokens[index].Type = TOKEN_OPERATOR_ADD;
                goto done;
            case '-':
                result->Tokens[index].Type = TOKEN_OPERATOR_SUBTRACT;
                goto done;
            case '*':
                result->Tokens[index].Type = TOKEN_OPERATOR_MULTIPLY;
                goto done;
            case '/':
                result->Tokens[index].Type = TOKEN_OPERATOR_DIVIDE;
                goto done;
        }

    done:
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

    free(lexemes->Tokens);
    free(lexemes);

    printf("\n");
}

