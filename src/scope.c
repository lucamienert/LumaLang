#include "include/scope.h"

scope_t *new_scope()
{
    scope_t *scope = malloc(sizeof(struct SCOPE_STRUCT));
    scope->function_definitions = (void*) 0;
    scope->function_definitions_size = 0;
    scope->variable_definitions = (void*) 0;
    scope->variable_definitions_size = 0;
    return scope;
}

ast_t *add_function_definition(scope_t *scope, ast_t *ast)
{
    scope->function_definitions_size++;
    if(scope->function_definitions == (void*)0)
        scope->function_definitions = malloc(sizeof(struct AST_STRUCT*));
    else
        scope->function_definitions = realloc(
            scope->function_definitions,
            scope->function_definitions_size * sizeof(struct AST_STRUCT**)
        );

    scope->function_definitions[scope->function_definitions_size-1] = ast;
    return ast;
}

ast_t *get_function_definition(scope_t *scope, const char *name)
{
    for(int i = 0; i < scope->function_definitions_size; ++i)
    {
        ast_t *ast = scope->function_definitions[i];
        if(strcmp(ast->function_definition_name, name) == 0)
            return ast;
    }

    return (void*) 0;
}

ast_t *add_variable_definition(scope_t *scope, ast_t *ast)
{
    if (scope->variable_definitions == (void*) 0)
    {
        scope->variable_definitions = malloc(sizeof(struct AST_STRUCT*));
        scope->variable_definitions[0] = ast;
        scope->variable_definitions_size++;
    }
    else
    {
        scope->variable_definitions_size++;
        scope->variable_definitions = realloc(
            scope->variable_definitions,
            scope->variable_definitions_size * sizeof(struct AST_STRUCT*)  
        );
        scope->variable_definitions[scope->variable_definitions_size-1] = ast;
    }

    return ast;
}

ast_t *get_variable_definition(scope_t *scope, const char *name)
{
    for (int i = 0; i < scope->variable_definitions_size; ++i)
    {
        ast_t *ast = scope->variable_definitions[i];
        if (strcmp(ast->variable_definition_name, name) == 0)
            return ast;
    }

    return (void*) 0;
}
