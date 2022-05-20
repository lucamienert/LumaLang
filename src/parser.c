#include "include/parser.h"

parser_t *new_parser(tokenizer_t *tokenizer)
{
    parser_t *parser = malloc(sizeof(struct PARSER_STRUCT));
    parser->tokenizer = tokenizer;
    parser->current_token = get_next_token(tokenizer);
    parser->previous_token = parser->current_token;
    parser->scope = new_scope();
    return parser;
}

void eat(parser_t *parser, int token_type)
{
    if(parser->current_token->type == token_type)
    {
        parser->previous_token = parser->current_token;
        parser->current_token = get_next_token(parser->tokenizer);
    }
    else
    {
        LOG("Unexpected token");
        exit(1);
    }
}

ast_t *parse(parser_t *parser, scope_t *scope)
{
    return parse_statements(parser, scope);
}

ast_t *parse_statement(parser_t *parser, scope_t *scope)
{
    switch (parser->current_token->type)
    {
        case TOKEN_ID: return parse_id(parser, scope);
    }

    return new_ast(AST_NOOP);
}

ast_t *parse_statements(parser_t *parser, scope_t *scope)
{
    ast_t *compound = new_ast(AST_COMPOUND);
    compound->scope = scope;
    compound->compound_value = malloc(sizeof(struct AST_STRUCT*));

    ast_t *ast_statement = parse_statement(parser, scope);
    ast_statement->scope = scope;
    compound->compound_value[0] = ast_statement;
    compound->compound_size += 1;

    while (parser->current_token->type == TOKEN_SEMI)
    {
        eat(parser, TOKEN_SEMI);

        ast_t *ast_statement = parse_statement(parser, scope);

        if (ast_statement)
        {
            compound->compound_size += 1;
            compound->compound_value = realloc(
                compound->compound_value,
                compound->compound_size  *sizeof(struct AST_STRUCT*)
            );
            compound->compound_value[compound->compound_size-1] = ast_statement;
        }
    }

    return compound;
}

ast_t *parse_expr(parser_t *parser, scope_t *scope)
{
    switch (parser->current_token->type)
    {
        case TOKEN_STRING: return parse_string(parser, scope);
        case TOKEN_ID: return parse_id(parser, scope);
    }

    return new_ast(AST_NOOP);
}

ast_t *parser_parse_factor(parser_t *parser, scope_t *scope)
{
}

ast_t *parser_parse_term(parser_t *parser, scope_t *scope)
{
}

ast_t *parse_function_call(parser_t *parser, scope_t *scope)
{
    ast_t *function_call = new_ast(AST_FUNCTION_CALL);

    function_call->function_call_name = parser->previous_token->value;
    eat(parser, TOKEN_LPAREN); 

    function_call->function_call_arguments = malloc(sizeof(struct AST_STRUCT*));

    ast_t *ast_expr = parse_expr(parser, scope);
    function_call->function_call_arguments[0] = ast_expr;
    function_call->function_call_arguments_size += 1;

    while (parser->current_token->type == TOKEN_COMMA)
    {
        eat(parser, TOKEN_COMMA);

        ast_t *ast_expr = parse_expr(parser, scope);
        function_call->function_call_arguments_size += 1;
        function_call->function_call_arguments = realloc(
            function_call->function_call_arguments,
            function_call->function_call_arguments_size  *sizeof(struct AST_STRUCT*)
        );
        function_call->function_call_arguments[function_call->function_call_arguments_size-1] = ast_expr;
    }
    eat(parser, TOKEN_RPAREN);

    function_call->scope = scope;

    return function_call;
}

ast_t *parse_variable_definition(parser_t *parser, scope_t *scope)
{
    eat(parser, TOKEN_ID);
    char *variable_definition_name = parser->current_token->value;
    eat(parser, TOKEN_ID);
    eat(parser, TOKEN_EQUALS);
    ast_t *variable_definition_value = parse_expr(parser, scope);

    ast_t *variable_definition = new_ast(AST_VARIABLE_DEFINITION);
    variable_definition->variable_definition_name = variable_definition_name;
    variable_definition->variable_definition_value = variable_definition_value;

    variable_definition->scope = scope;

    return variable_definition;
}

ast_t *parse_function_definition(parser_t *parser, scope_t *scope)
{
    ast_t *ast = new_ast(AST_FUNCTION_DEFINITION);
    eat(parser, TOKEN_ID);

    char *function_name = parser->current_token->value;
    ast->function_definition_name = calloc(
        strlen(function_name) + 1, sizeof(char)
    );
    strcpy(ast->function_definition_name, function_name);
    eat(parser, TOKEN_ID);
    eat(parser, TOKEN_LPAREN);

    ast->function_definition_args = malloc(sizeof(struct AST_STRUCT*));

    ast_t *arg = parse_variable(parser, scope);
    ast->function_definition_args_size += 1;
    ast->function_definition_args[ast->function_definition_args_size-1] = arg;

    while (parser->current_token->type == TOKEN_COMMA)
    {
        eat(parser, TOKEN_COMMA);
        ast->function_definition_args_size += 1;
        ast->function_definition_args =
            realloc(
                ast->function_definition_args,
                ast->function_definition_args_size  *sizeof(struct AST_STRUCT*)
            );

        ast_t *arg = parse_variable(parser, scope);
        ast->function_definition_args[ast->function_definition_args_size-1] = arg;
    }

    eat(parser, TOKEN_RPAREN);
    eat(parser, TOKEN_LBRACE);
    ast->function_definition_body = parse_statements(parser, scope);
    eat(parser, TOKEN_RBRACE);
    ast->scope = scope;

    return ast;
}

ast_t *parse_variable(parser_t *parser, scope_t *scope)
{
    char *token_value = parser->current_token->value;
    eat(parser, TOKEN_ID);

    if (parser->current_token->type == TOKEN_LPAREN)
        return parse_function_call(parser, scope);

    ast_t *ast_variable = new_ast(AST_VARIABLE);
    ast_variable->variable_name = token_value;
    ast_variable->scope = scope;

    return ast_variable;
}

ast_t *parse_string(parser_t *parser, scope_t *scope)
{
    ast_t *ast_string = new_ast(AST_STRING);
    ast_string->string_value = parser->current_token->value;
    eat(parser, TOKEN_STRING);
    ast_string->scope = scope;

    return ast_string;
}

ast_t *parse_id(parser_t *parser, scope_t *scope)
{
    if (strcmp(parser->current_token->value, "def") == 0)
        return parse_variable_definition(parser, scope);
    else if (strcmp(parser->current_token->value, "fun") == 0)
        return parse_function_definition(parser, scope);
    else
        return parse_variable(parser, scope);
}
