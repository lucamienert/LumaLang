#include "include/token.h"

Token::Token(std::string value, Type type)
{
    this->value = value;
    this->type = type;
}

std::string Token::get_value()
{
    return value;
}

Type Token::get_type()
{
    return type;
}