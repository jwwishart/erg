// Copyright (c) 2016 Justin William Wishart
// Full License is found in the LICENSE.txt file

#include "os.h"
#include "erg.h"
#include "compiler_arguments.h"
#ifdef DEBUG 
    #include "compiler_debug.h"
#endif

#include <stdio.h>  // printf
#include <assert.h> // assert


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

int main(int argc, char *argv[]) {
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
}

