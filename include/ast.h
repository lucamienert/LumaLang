#ifndef LUMALANG_AST_H_
#define LUMALANG_AST_H_

#pragma once

#include <string>
#include <cstdint>
#include <list.h>

enum SyntaxType
{
    ST_COMPOUND,
    ST_FUNCTION,
    ST_CALL,
    ST_ASSIGNMENT,
    ST_DEFINITION_TYPE,
    ST_VARIABLE,
    ST_STATEMENT,
    ST_INT,
    ST_STRING,
    ST_NOOP,
};

class AST
{
private:
    SyntaxType type;
    List *children;
    std::string name;
    AST *value;
    int32_t int_value;
    int32_t data_type;

public:
    AST(SyntaxType type);

    std::string getName();
    void setName(std::string name);
    
    AST *getValue();
    void setValue(AST *value);

    int32_t getDataType();
    void setDataType(int32_t type);
    
    SyntaxType getType();
    void setType(SyntaxType type);

    int32_t getIntValue();
    void setIntValue(int32_t value);

    List *getChildren();
};

#endif