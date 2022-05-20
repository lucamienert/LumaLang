#include <luma.h>
#include <parser.h>
#include <tokenizer.h>
#include <ast.h>
#include <asm_frontend.h>

void compile(std::string filename)
{
    std::string source = get_file_content(filename);

    Tokenizer *tokenizer = new Tokenizer(source);
    Praser *parser = new Parser(tokenizer);
    AST *root = parser->parse();

    std::string s = asm_f_root(root);

    std::fstream out;
    out.open("test.s", ios::out);
    if(!out.good())
        exit(1);

    out << s;
    out.close();

    shell_command("as test.s -o test.o");
    shell_command("ld test.o -o test.out");
}