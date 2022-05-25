#ifndef LUMALANG_TOKENIZER_H_
#define LUMALANG_TOKENIZER_H_

#pragma once

#include <token.h>
#include <iostream>

class Tokenizer
{
private:
    std::string source;
    char current;
    int source_size;
    int index;
 
public:
    Tokenizer(std::string source);

    void next();
    void skip_whitespace();
    void skip_comment();
    
    char peek(int buffer);

    Token *move_with_token(Token *token);
    Token *move_current(Type type);
    Token *next_token();
    Token *parse_id();
    Token *parse_number();
};

#endif
