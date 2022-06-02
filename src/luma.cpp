#include <luma.h>
#include <parser.h>
#include <tokenizer.h>
#include <ast.h>
#include <asm_frontend.h>

void compile(std::string filename)
{
    std::string source = get_file_content(filename);

    Tokenizer *tokenizer = new Tokenizer(source);
    Parser *parser = new Parser(tokenizer);
    AST *root = parser->parse();

    std::string s = asm_f_root(root);

    std::fstream out;
    out.open("output.s", std::ios::out);
    if(!out.good())
        exit(1);

    out << s;
    out.close();

    shell_command("as output.s -o output.o");
    shell_command("ld output.o -o output.out");
}
