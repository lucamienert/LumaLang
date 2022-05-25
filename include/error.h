#ifndef LUMALANG_ERROR_H_
#define LUMALANG_ERROR_H_

#pragma once

#include <iostream>
#include <string>

enum Error
{
    ERROR_UNEXPECTED_TOKEN,
    ERROR_WRONG_AST_TYPE
}

std::string type_to_string(int type)
{
    switch(type)
    {
        case ERROR_UNEXPECTED_TOKEN: return "ERROR_UNEXPECTED_TOKEN";
        case ERROR_WRONG_AST_TYPE: return "ERROR_WRONG_AST_TYPE";
    }

    return "Unable to stringify";
}

void log(std::string content, int errno)
{
    std::cout << "[LUMALANG]: " << content << " (" << type_to_string(errno) << ")" << std::endl;
}

void log(int content, int errno)
{
    std::cout << "[LUMALANG]: " << content << " (" << type_to_string(errno) << ")" << std::endl;
}

#endif