
#ifndef TOKENIZER_H
#define TOKENIZER_H

#ifdef __cplusplus
extern "C" {
#endif

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


// Prototypes
//

TokenArray *lex(char *code);


#ifdef __cplusplus
}
#endif

#endif /* TOKENIZER_H */