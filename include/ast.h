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
    int int_value;
    int data_type;

public:
    AST(SyntaxType type);

    std::string get_name();
    void set_name(std::string name);
    
    AST *get_value();
    void set_value(AST *value);

    int get_datatype();
    void set_datatype(int type);
    
    SyntaxType get_type();
    void set_type(SyntaxType type);

    int get_intvalue();
    void set_intvalue(int value);

    List *get_children();
};

#endif