#include "include/ast.h"

AST::AST(SyntaxType type)
{
    this->type = type;

    if(type == ST_COMPOUND)
        this->children = new List(sizeof(AST*));
}

std::string AST::get_name()
{
    return name;
}

void AST::set_name(std::string name)
{
    this->name = name;
}

AST *AST::get_value()
{
    return value;
}

void AST::set_value(AST *value)
{
    this->value = value;
}

int32_t AST::get_datatype()
{
    return data_type;
}

void AST::set_datatype(int32_t type)
{
    this->data_type = type;
}

SyntaxType AST::get_type()
{
    return type;
}

void AST::set_type(SyntaxType type)
{
    this->type = type;
}

int32_t AST::get_intvalue()
{
    return int_value;
}

void AST::set_intvalue(int32_t value)
{
    this->int_value = value;
}

List *AST::get_children()
{
    return children;
}
