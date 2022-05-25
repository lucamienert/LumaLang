#ifndef LUMALANG_TOKEN_H_
#define LUMALANG_TOKEN_H_

#pragma once

#include <string>

enum Type
{
    TOKEN_ID,
    TOKEN_INT,
    TOKEN_END_OF_FILE,
    TOKEN_STRING,
    TOKEN_IF,
    TOKEN_WHILE,
    TOKEN_LET,
    TOKEN_FUN,
    TOKEN_RETURN,
    TOKEN_LEFT_PAREN,    // (
    TOKEN_RIGHT_PAREN,   // )
    TOKEN_LEFT_BRACKET,  // [
    TOKEN_RIGHT_BRACKET, // ]
    TOKEN_LEFT_BRACE,    // {
    TOKEN_RIGHT_BRACE,   // }
    TOKEN_COMMA,         // ,
    TOKEN_SEMICOLON,     // ;
    TOKEN_COLON,         // :
    TOKEN_PLUS,          // +
    TOKEN_MINUS,         // -
    TOKEN_AMPERSAND,     // &
    TOKEN_ASTERISK,      // *
    TOKEN_EQUALS,        // =
    TOKEN_EXCLAMATION,   // !
    TOKEN_AND,           // &&
    TOKEN_OR,            // ||
    TOKEN_NOT_EQUAL,     // !=
    TOKEN_DOUBLE_EQUAL,  // ==
};

class Token
{
private:
    std::string value;
    Type type;

public:
    Token(std::string value, Type type);
    std::string get_value();
    Type get_type();
};

#endif