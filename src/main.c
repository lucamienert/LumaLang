#include <stdio.h>
#include <stdlib.h>

#include "include/misc.h"
#include "include/io.h"
#include "include/tokenizer.h"
#include "include/parser.h"
#include "include/ast.h"
#include "include/visitor.h"

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        LOG("You must provide an file ending with '.lcl'");
        exit(0);
    }

    tokenizer_t *tokenizer = new_tokenizer(get_file(argv[1]));
    parser_t *parser = new_parser(tokenizer);
    ast_t *root_node = parse(parser, parser->scope);
    visitor_t *visitor = new_visitor();
    visit(visitor, root_node);

    return 0;
}