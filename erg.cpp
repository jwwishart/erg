#include <stdio.h>

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


struct Token {
    TokenType type;
};


// TODO 
void lex(char *code) {
    while (true) {
        printf("test\n");
        break;     
    }

    return;
}


int main() {
    lex((char *)"Hello World!");

    printf("Hello World\n");
}

