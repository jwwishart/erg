#ifndef TOKENIZER_CPP
#define TOKENIZER_CPP

#include <stdlib.h>
#include <assert.h>

#include "tokenizer.h"
#include "../misc/string_builder.h"


// TODO cleanup
// TODO extra checks
// TODO(jwwishart): not available externally?
void 
ensure_token_array_size(TokenArray *array) {
    if (array->Length >= array->Capacity) {
        auto currentCapacity = array->Capacity;
        auto newCapacity     = array->Capacity * 2;

        array->Tokens = (Token*)realloc(array->Tokens, sizeof(Token) * newCapacity);

        array->Capacity = newCapacity;
    }
}


#ifdef __cplusplus
extern "C" {
#endif

TokenArray *lex(char *code) {
    assert(code != NULL);

    auto result = (TokenArray *)malloc(sizeof(TokenArray));
    result->Length   = 0;
    result->Capacity = 4;
    result->Tokens = (Token*)malloc(sizeof(Token) * 4);

    char *c = code;
    int  tokenIndex = 0; // Index into the Token Array
    int  line = 1;
    int  column = 1;

    // TODO(jwwishart) this ought to be added to for all whitespace and 
    //  pointer assigned to token->PrefixedWhitespace before adding a usefull, non-whitespace
    //  token
    auto whitespace = allocate_string_builder();

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

#ifdef __cplusplus
}
#endif

#endif /* TOKENIZER_CPP */