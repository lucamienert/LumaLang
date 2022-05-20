#ifndef LUMALANG_PARSER_H_
#define LUMALANG_PARSER_H_

#pragma once

#include <token.h>
#include <tokenizer.h>
#include <list.h>

class Parser
{
private:
    Tokenizer *tokenizer;
    Token *token;

public:
    Parser(Tokenizer *tokenizer);
    Token *eat(Type type);
    AST *parse();
    AST *parse_id();
    AST *parse_block();
    AST *parse_expression();
    AST *parse_int();
    AST *parse_string();
    AST *parse_statement();
    AST *parse_compound();
    AST *parse_conditional();
    AST *parse_loop();
    AST *parse_return();
    AST *parse_definition();
};

#endif