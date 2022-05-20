#ifndef TOKENIZER_H_
#define TOKENIZER_H_

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <ctype.h>

#include "token.h"

typedef struct TOKENIZER_STRUCT
{
    char *source;
    char current;
    uint32_t index;
} tokenizer_t;

tokenizer_t *new_tokenizer(char *source);

void next_character(tokenizer_t *tokenizer);
void skip_whitespace(tokenizer_t *tokenizer);

token_t *get_next_token(tokenizer_t *tokenizer);
token_t *get_string(tokenizer_t *tokenizer);
token_t *get_id(tokenizer_t *tokenizer);
token_t *move_with_token(tokenizer_t *tokenizer, token_t *token);

char *get_char_as_string(tokenizer_t *tokenizer);

#endif