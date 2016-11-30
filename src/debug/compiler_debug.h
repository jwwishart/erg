// Copyright (c) 2016 Justin William Wishart
// Full License is found in the LICENSE.txt file

#ifndef COMPILER_DEBUG_H
#define COMPILER_DEBUG_H

#ifdef __cplusplus
extern "C" {
#endif


#ifdef DEBUG

#include "../tokenizer/tokenizer.h"

void print_token_type(TokenType type) 
{
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

    printf("*** Unsupported Token Type given to print_token_type() ***");
}


void print_token(Token * token) 
{
    printf("  (L%d:C%d:Len%d) > ",  token->Line, token->Column, token->Length);
    print_token_type(token->Type);

    if (token->Type == TOKEN_NUMBER) {
        printf(" > %s", token->Raw); // Should never be null
    }
}

void print_token_array(TokenArray * array) 
{
    for (auto i = 0; i < array->Length; i++) {
        print_token(&array->Tokens[i]);
        
        printf("\n");
    }
}

#endif // DEBUG


#ifdef __cplusplus
}
#endif

#endif /* COMPILER_DEBUG_H */

