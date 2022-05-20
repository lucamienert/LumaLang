#ifndef AST_H_
#define AST_H_

#include <stdlib.h>

typedef struct AST_STRUCT
{
    enum
    {
        AST_VARIABLE,
        AST_VARIABLE_DEFINITION,

        AST_FUNCTION_CALL,
        AST_FUNCTION_DEFINITION,

        AST_STRING,
        AST_COMPOUND,
        AST_NOOP
    } type;

    struct SCOPE_STRUCT *scope;

    char *variable_name;
    char *variable_definition_name;
    struct AST_STRUCT *variable_definition_value;

    char *function_call_name;
    struct AST_STRUCT **function_call_arguments;
    size_t function_call_arguments_size;
    struct AST_STRUCT *function_definition_body;
    char *function_definition_name;
    struct AST_STRUCT **function_definition_args;
    size_t function_definition_args_size;

    struct AST_STRUCT **compound_value;
    size_t compound_size;

    char *string_value;

} ast_t;

ast_t *new_ast(int type);

#endif