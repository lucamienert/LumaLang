#include "include/visitor.h"
#include "include/misc.h"
#include "include/scope.h"

visitor_t *new_visitor()
{
    visitor_t *visitor = malloc(sizeof(struct VISITOR_STRUCT));
    return visitor;
}

ast_t *visit(visitor_t *visitor, ast_t *node)
{
    switch (node->type)
    {
        case AST_VARIABLE_DEFINITION: return visit_variable_definition(visitor, node); break;
        case AST_FUNCTION_DEFINITION: return visit_function_definition(visitor, node); break;
        case AST_VARIABLE: return visit_variable(visitor, node); break;
        case AST_FUNCTION_CALL: return visit_function_call(visitor, node); break;
        case AST_STRING: return visit_string(visitor, node); break;
        case AST_COMPOUND: return visit_compound(visitor, node); break;
        case AST_NOOP: return node; break;
    }

    LOG("Uncaught statement");
    exit(1);

    return new_ast(AST_NOOP);
}

ast_t *visit_variable_definition(visitor_t *visitor, ast_t *node)
{
    add_variable_definition(node->scope, node);
    return node;
}

ast_t *visit_function_definition(visitor_t *visitor, ast_t *node)
{
    add_function_definition(node->scope, node);
    return node;
}

ast_t *visit_variable(visitor_t *visitor, ast_t *node)
{
    ast_t* ast = get_variable_definition(node->scope, node->variable_name);
    if(ast != (void*) 0)
        return visit(visitor, ast->variable_definition_value);

    LOG("Undefined variable");
    exit(1);
}

/* BUILT INS */
static ast_t *builtin_function_sysout(visitor_t *visitor, ast_t **args, int args_size)
{
    for (int i = 0; i < args_size; ++i)
    {
        ast_t* visited_ast = visit(visitor, args[i]);

        switch (visited_ast->type)
        {
            case AST_STRING: printf("%s\n", visited_ast->string_value); break;
            default: printf("%p\n", visited_ast); break;
        }
    }

    return new_ast(AST_NOOP);
}
/* END */

ast_t *visit_function_call(visitor_t *visitor, ast_t *node)
{
    if (strcmp(node->function_call_name, "sysout") == 0)
        return builtin_function_sysout(visitor, node->function_call_arguments, node->function_call_arguments_size);

    ast_t *fdef = get_function_definition(
        node->scope,
        node->function_call_name
    );

    if (fdef == (void*)0)
    {
        LOG("Undefined method");
        exit(1);
    }

    for (int i = 0; i < (int) node->function_call_arguments_size; ++i)
    {
        ast_t* ast_var = (ast_t*) fdef->function_definition_args[i];
        ast_t* ast_value = (ast_t*) node->function_call_arguments[i];

        ast_t* ast_vardef = new_ast(AST_VARIABLE_DEFINITION);
        ast_vardef->variable_definition_value = ast_value;

        ast_vardef->variable_definition_name = (char*) calloc(strlen(ast_var->variable_name) + 1, sizeof(char));
        strcpy(ast_vardef->variable_definition_name, ast_var->variable_name);

        add_variable_definition(fdef->function_definition_body->scope, ast_vardef);
    }
    
    return visit(visitor, fdef->function_definition_body);
}

ast_t *visit_string(visitor_t *visitor, ast_t *node)
{
    return node;
}

ast_t *visit_compound(visitor_t *visitor, ast_t *node)
{
    for (int i = 0; i < node->compound_size; ++i)
        visit(visitor, node->compound_value[i]);

    return new_ast(AST_NOOP);
}