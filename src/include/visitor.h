#ifndef VISITOR_H_
#define VISITOR_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ast.h"

typedef struct VISITOR_STRUCT {} visitor_t;

visitor_t *new_visitor();

ast_t *visit(visitor_t *visitor, ast_t *node);
ast_t *visit_variable_definition(visitor_t *visitor, ast_t *node);
ast_t *visit_function_definition(visitor_t *visitor, ast_t *node);
ast_t *visit_variable(visitor_t *visitor, ast_t *node);
ast_t *visit_function_call(visitor_t *visitor, ast_t *node);
ast_t *visit_string(visitor_t *visitor, ast_t *node);
ast_t *visit_compound(visitor_t *visitor, ast_t *node);

#endif