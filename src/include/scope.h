#ifndef SCOPE_H_
#define SCOPE_H_

#include <string.h>

#include "ast.h"

typedef struct SCOPE_STRUCT
{
    ast_t **function_definitions;
    size_t function_definitions_size;

    ast_t **variable_definitions;
    size_t variable_definitions_size;
} scope_t;

scope_t *new_scope();

ast_t *add_function_definition(scope_t *scope, ast_t *ast);
ast_t *get_function_definition(scope_t *scope, const char *name);
ast_t *add_variable_definition(scope_t *scope, ast_t *ast);
ast_t *get_variable_definition(scope_t *scope, const char *name);

#endif