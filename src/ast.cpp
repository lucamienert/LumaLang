#include <ast.h>

AST::AST(SyntaxType type)
{
    this->type = type;

    if(type == ST_COMPOUND)
        this->children = new List(sizeof(AST*));
}

std::string AST::getName()
{
    return name;
}

void AST::setName(std::string name)
{
    this->name = name;
}

AST *AST::getValue()
{
    return value;
}

void AST::setValue(AST *value)
{
    this->value = value;
}

int32_t AST::getDataType()
{
    return data_type;
}

void AST::setDataType(int32_t type)
{
    this->data_type = type;
}

SyntaxType AST::getType()
{
    return type;
}

void AST::setType(SyntaxType type)
{
    this->type = type;
}

int32_t AST::getIntValue()
{
    return int_value;
}

void AST::setIntValue(int32_t value)
{
    this->int_value = value;
}

List *AST::getChildren()
{
    return children;
}
