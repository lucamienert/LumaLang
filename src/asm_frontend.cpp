#include "include/asm_frontend.h"

std::string section_data = ".data\n";
std::string section_bss = ".bss\n";

int string_counter = 1;

std::string constants = "";

static std::string asm_f_compound(AST *ast)
{
    std::string value = "";

    for(int i = 0; i < (int) ast->get_children()->get_size(); ++i)
    {
        AST *child = (AST*)ast->get_children()->get_items(i);
        std::string next = asm_f(child);
        value += next;
    }

    return value;
}

static std::string asm_f_assignment(AST *ast)
{
    std::string s = "";
    std::string name = ast->get_name();
    std::string value = ((AST*) ast->get_value()->get_children()->get_items(0))->get_name();

    if(value != "")
    {
        std::string assign_string = name + "_str: .ascii \"" + value + "\"\n" + name + "_str_len = .- " + name + "_str\n";
        section_data += assign_string;
    }
    else
    {
        int int_value = ((AST*) ast->get_value()->get_children()->get_items(0))->get_intvalue();
        std::string assign_int = name + ": .int " + std::to_string(int_value) + "\n" + name + "_str: .ascii \"" + std::to_string(int_value) + "\"\n" + name + "_str_len = .- " + name + "_str\n";
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

static std::string asm_f_int(AST *ast)
{
    return "";
}

static std::string asm_f_call(AST *ast)
{
    std::string s = "";

    if(ast->get_name() == "ret")
    {
        AST *arg = (AST*) (ast->get_value()->get_children()->get_size() ? ast->get_value()->get_children()->get_items(0) : nullptr);
        const std::string temp = "mov $" + std::to_string(arg ? arg->get_intvalue() : 0) + ", \%eax\n";

        s += temp;
        return s;
    }

    if(ast->get_name() == "sysout")
    {
        int num_of_arg = ((AST*)ast->get_value()->get_children()->get_items(0))->get_children()->get_size();

        for (int i = 0; i < num_of_arg; i++)
        {
            AST *print_arg = ((AST*)((AST*)ast->get_value()->get_children()->get_items(0))->get_children()->get_items(i));

            if (print_arg->get_type() == ST_STRING || print_arg->get_type() == ST_INT)
            {
                std::string value = "";

                if (print_arg->get_type() == ST_INT)
                    value = std::to_string(print_arg->get_intvalue());
                else
                    value = print_arg->get_name();

                std::string define = 
                    "text" + std::to_string(string_counter) + ": .ascii \"" + value + "\"\n" \
                    "text" + std::to_string(string_counter) + "_len = .- text" + std::to_string(string_counter) + "\n";

                const std::string print = 
                    "mov $4, %eax\n" \
                    "mov $1, %ebx\n" \
                    "mov $text" + std::to_string(string_counter) + ", %ecx\n" \
                    "mov $text" + std::to_string(string_counter) + "_len, %edx\n" \
                    "int $0x80\n";

                string_counter++;

                s += print;
                section_data += define;
            }
            else if (print_arg->get_type() == ST_VARIABLE)
            {
                std::string var_name = print_arg->get_name();

                const std::string print = 
                    "mov $4, %eax\n" \
                    "mov $1, %ebx\n" \
                    "mov $" + var_name + "_str , %ecx\n" \
                    "mov $" + var_name + "_str_len, %edx\n" \
                    "int $0x80\n";

                s += print;
            }
        }

        return s;
    }

    if(ast->get_name() == "sysin")
    {
        AST *scan_arg = ((AST*)((AST*) ast->get_value()->get_children()->get_items(0))->get_children()->get_items(0));
        if (scan_arg->get_type() == ST_VARIABLE)
        {
            std::string var_name = scan_arg->get_name();
            
            const std::string scan =
                "mov $3, %eax\n" \
                "mov $0, %ebx\n" \
                "mov $" + var_name + "_str, %ecx\n" \
                "mov $" + var_name + "_str_len, %edx\n" \
                "int $0x80\n";

            s += scan;
        }

        return s;
    }

    s += "call " + ast->get_name() + "\n";

    return s;
}

static std::string asm_f_function(AST* ast)
{
    std::string s;

    if (ast->get_value()->get_type() == ST_CALL)
    {
        std::string call = asm_f_call(ast);
        return call;
    }

    const std::string temp = ".global " + ast->get_name() + "\n" + ast->get_name() + ":\n";

    s = temp;

    AST* as_val = ast->get_value();

    std::string val = asm_f(as_val->get_value());

    s += val;
    s += "ret\n";

    return s;
}

std::string asm_f_root(AST *ast)
{
    const std::string text = 
        ".text\n" \
        ".global _start\n" \
        "_start:\n" \
        "call main\n" \
        "mov \%eax, \%ebx\n" \
        "mov $1, \%eax\n" \
        "int $0x80\n\n";

    std::string value = text;
    std::string next = asm_f(ast);

    value += next;

    std::string result = "";
    result += constants;
    result += section_data;
    result += section_bss;
    result += value;

    return result;
}

std::string asm_f(AST *ast)
{
    std::string value = "";
    std::string next_value = "";

    switch (ast->get_type())
    {
        case ST_COMPOUND:
            next_value = asm_f_compound(ast);
            break;
        case ST_ASSIGNMENT:
            next_value = asm_f_assignment(ast);
            break;
        case ST_VARIABLE:
            next_value = asm_f_variable(ast);
            break;
        case ST_CALL:
            next_value = asm_f_call(ast);
            break;
        case ST_INT:
            next_value = asm_f_int(ast);
            break;
        case ST_FUNCTION:
            next_value = asm_f_function(ast);
            break;
        default: exit(1);
    }

    value += next_value;

    return value;
}