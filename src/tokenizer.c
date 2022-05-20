#include "include/tokenizer.h"
#include "include/misc.h"

tokenizer_t *new_tokenizer(char *source)
{
    tokenizer_t *tokenizer = malloc(sizeof(struct TOKENIZER_STRUCT));
    tokenizer->source = source;
    tokenizer->index = 0;
    tokenizer->current = tokenizer->source[tokenizer->index];

    return tokenizer;
}

void next_character(tokenizer_t *tokenizer)
{
    if(tokenizer->current == '\0' && tokenizer->index > strlen(tokenizer->source))
        return;
        
    tokenizer->index++;
    tokenizer->current = tokenizer->source[tokenizer->index];
}

void skip_whitespace(tokenizer_t *tokenizer)
{
    while(tokenizer->current == ' ' || tokenizer->current == 10)
        next_character(tokenizer);
}

token_t *get_next_token(tokenizer_t *tokenizer)
{
    while(tokenizer->current != '\0' && tokenizer->index < strlen(tokenizer->source))
    {
        if(tokenizer->current == ' ' || tokenizer->current == 10)
            skip_whitespace(tokenizer);

        if(isalnum(tokenizer->current))
            return get_id(tokenizer);

        if(tokenizer->current == '"')
            return get_string(tokenizer);

        switch(tokenizer->current)
        {
            case '=': return move_with_token(tokenizer, new_token(TOKEN_EQUALS, get_char_as_string(tokenizer))); break;
            case ';': return move_with_token(tokenizer, new_token(TOKEN_SEMI, get_char_as_string(tokenizer))); break;
            case '(': return move_with_token(tokenizer, new_token(TOKEN_LPAREN, get_char_as_string(tokenizer))); break;
            case ')': return move_with_token(tokenizer, new_token(TOKEN_RPAREN, get_char_as_string(tokenizer))); break;
            case '{': return move_with_token(tokenizer, new_token(TOKEN_LBRACE, get_char_as_string(tokenizer))); break;
            case '}': return move_with_token(tokenizer, new_token(TOKEN_RBRACE, get_char_as_string(tokenizer))); break;
            case ',': return move_with_token(tokenizer, new_token(TOKEN_COMMA, get_char_as_string(tokenizer))); break;
            case '+': return move_with_token(tokenizer, new_token(TOKEN_PLUS, get_char_as_string(tokenizer))); break;
            case '-': return move_with_token(tokenizer, new_token(TOKEN_MINUS, get_char_as_string(tokenizer))); break;
            case '*': return move_with_token(tokenizer, new_token(TOKEN_ASTR, get_char_as_string(tokenizer))); break;
            case '/': return move_with_token(tokenizer, new_token(TOKEN_DIVIDER, get_char_as_string(tokenizer))); break;
            case '%': return move_with_token(tokenizer, new_token(TOKEN_MODULO, get_char_as_string(tokenizer))); break;
            case '<': return move_with_token(tokenizer, new_token(TOKEN_LESS_THAN, get_char_as_string(tokenizer))); break;
            case '>': return move_with_token(tokenizer, new_token(TOKEN_GREATER_THAN, get_char_as_string(tokenizer))); break;
        }
    }

    return new_token(TOKEN_EOF, "\0");
}

token_t *get_string(tokenizer_t *tokenizer)
{
    next_character(tokenizer);

    char *value = malloc(sizeof(char));
    value[0] = '\0';

    while(tokenizer->current != '"')
    {
        char *string = get_char_as_string(tokenizer);
        value = realloc(value, (strlen(value) + strlen(string) + 1) * sizeof(char));
        strcat(value, string);

        next_character(tokenizer);
    }

    next_character(tokenizer);
    return new_token(TOKEN_STRING, value);
}

token_t *get_id(tokenizer_t *tokenizer)
{
    char *value = malloc(sizeof(char));
    value[0] = '\0';

    while(isalnum(tokenizer->current))
    {
        char *string = get_char_as_string(tokenizer);
        value = realloc(value, (strlen(value) + strlen(string) + 1) * sizeof(char));
        strcat(value, string);

        next_character(tokenizer);
    }

    return new_token(TOKEN_ID, value);
}

token_t *move_with_token(tokenizer_t *tokenizer, token_t *token)
{
    next_character(tokenizer);
    return token;
}

char *get_char_as_string(tokenizer_t *tokenizer)
{
    char* string = calloc(2, sizeof(char));
    string[0] = tokenizer->current;
    string[1] = '\0';

    return string;
}