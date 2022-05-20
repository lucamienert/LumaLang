#ifndef TOKEN_H_
#define TOKEN_H_

#include <stdlib.h>

typedef struct TOKEN_STRUCT
{
    enum
    {
        TOKEN_ID,
        TOKEN_EOF,

        TOKEN_STRING,

        TOKEN_LPAREN,
        TOKEN_RPAREN,
        TOKEN_LBRACE,
        TOKEN_RBRACE,

        TOKEN_LESS_THAN,
        TOKEN_GREATER_THAN,

        TOKEN_EQUALS,
        TOKEN_NOT_EQUALS,

        TOKEN_PLUS,
        TOKEN_MINUS,
        TOKEN_ASTR,
        TOKEN_DIVIDER,
        TOKEN_MODULO,

        TOKEN_ARROW,

        TOKEN_SEMI,
        TOKEN_COMMA,
    } type;
    char *value;
} token_t;

token_t *new_token(int type, char *value);

#endif