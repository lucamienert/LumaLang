#include <parser.h>

Parser::Parser(Tokenizer *tokenizer)
{
    this->tokenizer = tokenizer;
    this->token = tokenizer->next_token();
}

Token *Parser::eat(Type type)
{
    if(token->get_type() != type)
        exit(1);

    token = tokenizer->next_token();
    return token;
}

AST *Parser::parse()
{
    return parse_compound();
}

AST *Parser::parse_id()
{
    std::string value = token->get_value();
    eat(TOKEN_ID);

    if (value == "sysout")
    {
        AST *ast = new AST(ST_CALL);
        ast->set_name(value);
        ast->set_value(parse_block());
        return ast;
    }

    if (value == "sysin")
    {
        AST *ast = new AST(ST_CALL);
        ast->set_name(value);
        ast->set_value(parse_block());
        return ast;
    }

    if (token->get_type() == TOKEN_EQUALS)
    {
        eat(TOKEN_EQUALS);
        AST *ast = new AST(ST_ASSIGNMENT);
        ast->set_name(value);
        ast->set_value(parse_expression());
        return ast;
    }

    AST *ast = new AST(ST_VARIABLE);
    ast->set_name(value);

    if(token->get_type() == TOKEN_LEFT_PAREN)
    {
        ast->set_type(ST_FUNCTION);
        ast->set_value(parse_block());
    }

    return ast;
}

AST *Parser::parse_block()
{
    eat(TOKEN_LEFT_PAREN);

    AST *ast = new AST(ST_COMPOUND);

    while(token->get_type() != TOKEN_RIGHT_PAREN)
        (ast->get_children())->list_push(parse_expression());

    eat(TOKEN_RIGHT_PAREN);

    if(token->get_type() == TOKEN_LEFT_BRACE)
    {
        ast->set_type(ST_FUNCTION);
        ast->set_value(parse_compound());
    }
    else
        ast->set_type(ST_CALL);

    return ast;
}

AST *Parser::parse_expression()
{
    AST *ast = new AST(ST_COMPOUND);

    (ast->get_children())->list_push(parse_statement());

    while(token->get_type() == TOKEN_COMMA)
    {
        eat(TOKEN_COMMA);
        (ast->get_children())->list_push(parse_statement());
    }

    return ast;
}

AST *Parser::parse_int()
{
    int value = stoi(token->get_value());
    eat(TOKEN_INT);

    AST *ast = new AST(ST_INT);
    ast->set_intvalue(value);

    return ast;
}

AST *Parser::parse_string()
{
    std::string value = token->get_value();
    eat(TOKEN_STRING);

    AST *ast = new AST(ST_STRING);
    ast->set_name(value);

    return ast;
}

AST *Parser::parse_statement()
{
    switch(token->get_type())
    {
        case TOKEN_ID: return parse_id();
        case TOKEN_LEFT_PAREN: return parse_block();
        case TOKEN_INT: return parse_int();
        case TOKEN_IF: return parse_conditional();
        case TOKEN_WHILE: return parse_loop();
        case TOKEN_RETURN: return parse_return();
        case TOKEN_LET: return parse_definition();
        case TOKEN_STRING: return parse_string();
        default: exit(1);
    }
}

AST *Parser::parse_compound()
{
    eat(TOKEN_FUN);
    bool should_close = false;

    if (token->get_type() == TOKEN_LEFT_BRACE)
    {
        eat(TOKEN_LEFT_BRACE);
        should_close = true;
    }

    AST *compound = new AST(ST_COMPOUND);

    while (token->get_type() != TOKEN_END_OF_FILE && token->get_type() != TOKEN_RIGHT_BRACE)
    {
        (compound->get_children())->list_push(parse_statement());

        if (token->get_type() == TOKEN_SEMICOLON)
            eat(TOKEN_SEMICOLON);
    }

    if (should_close)
        eat(TOKEN_RIGHT_BRACE);

    return compound;
}

AST *Parser::parse_conditional() 
{
    return new AST(ST_NOOP);
}

AST *Parser::parse_loop() 
{
    return new AST(ST_NOOP);
}

AST *Parser::parse_return()
{
    eat(TOKEN_RETURN);

    AST *ast = new AST(ST_CALL);
    ast->set_name("ret");
    ast->set_value(parse_expression());
    return ast;
}

AST *Parser::parse_definition()
{
    eat(TOKEN_LET);
    return parse_id();
}