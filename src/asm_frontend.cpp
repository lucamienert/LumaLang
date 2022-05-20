#include <asm_frontend.h>

std::string section_data = ".data\n";
std::string section_bss = ".bss\n";

int string_counter = 1;

std::string constants = "";

static std::string asm_f_compound(AST *ast)
{
    std::string value = "";

    for(int i = 0; i < (int) ast->get_children()->get_size(); ++i)
    {
        AST *child = ast->get_children()->get_items(i);
        std::string next = asm_f(child);
        value += next;
    }

    return value;
}

static std::string asm_f_assignment(AST *ast)
{
    std::string s = "";
    std::string name = ast->get_name();
    std::strig value = ((AST*) ast->get_value()->get_children()->get_items(0))->get_name();

    if(value != "")
    {
        std::string assign_string = name "_str: .ascii \"" + value + "\"\n" + name + "_str_len = .- " + name + "_str\n";
        section_data += assign_string;
    }
    else
    {
        int int_value = ((AST*) ast->get_value()->get_children()->get_items(0))->get_intvalue();
        std::string assign_int = name + ": .int " + to_string(int_value) + "\n" + name + "_str: .ascii \"" + to_string(int_value) + "\"\n" + name + "_str_len = .- " + name + "_str\n";
        section_data += assign_int;
    }

    return s;
}

static std::string asm_f_variable(AST *ast)
{
    std::string s = "";
    std::string name = ast->get_name();
    std::string declaration = name + ": .space " + name + "_len\n" + name + "_str: .space " + name + "_str_len\n";

    section_bss += declaration;

    constants += name + "_len = 200\n" + name + "_str_len = 200\n";

    return s;
}

std::string asm_f_root(AST *ast)
{

}

std::string asm_f(AST *ast)
{

}