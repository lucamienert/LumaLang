#include "include/token.h"

token_t *new_token(int type, char *value)
{
    token_t *token = malloc(sizeof(struct TOKEN_STRUCT));
    token->type = type;
    token->value = value;

    return token;
}