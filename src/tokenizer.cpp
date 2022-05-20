#include <tokenizer.h>

#define MIN(a, b) \
    a < b ? a : b

Lexer::Lexer(std::string source)
{
    this->source = source;
    this->index = 0;
    this->source_size = source.length();
    this->current = source[this->index];
}

void next()
{
    if(current == '\0' && index > source_size)
        return;

    ++index;
    current = source[index];
}

void skip_whitespace()
{
    while(current == 13 || current == 10 || current == ' ' || current == '\t')
        next();
}

void skip_comment()
{

}

char peek(int32_t buffer)
{
    return source[MIN(index + buffer, source_size)];
}

Token *move_with_token(Token *token)
{
    next();
    return token;
}

Token *move_current(Type type)
{
    std::string value = "";
    value += current;

    Token *token = new Token(value, type);
    next();
    return token;
}

Token *next_token()
{
    while(current != '\0')
    {
        skip_whitespace();

        if(isalpha(current))
            parse_id();

        if(isdigit(current))
            parse_number();

        switch(current)
        {
            case '(': return move_current(TOKEN_LEFT_PAREN);
            case ')': return move_current(TOKEN_RIGHT_PAREN);
            case '[': return move_current(TOKEN_LEFT_BRACKET);
            case ']': return move_current(TOKEN_RIGHT_BRACKET);
            case '{': return move_current(TOKEN_LEFT_BRACE);
            case '}': return move_current(TOKEN_RIGHT_BRACE);
            case ',': return move_current(TOKEN_COMMA);
            case ';': return move_current(TOKEN_SEMICOLON);
            case ':': return move_current(TOKEN_COLON);
            case '+': return move_current(TOKEN_PLUS);
            case '-': return move_current(TOKEN_MINUS);
            case '*': return move_current(TOKEN_ASTERISK);
            case '"': return this->lexer_parse_id();
            case '\0': break;
            default: exit(1); break;
        }
    }

    return new Token("\0", TOKEN_END_OF_FILE);
}

Token *parse_id()
{
    std::string value = "";

    if(current == '"')
    {
        next();

        while(current != '"')
        {
            value += current;
            next();
        }

        next();
        return new Token(value, TOKEN_STRING);
    }

    while(isalpha(current))
    {
        value += current;
        next();
    }

    Token *token = nullptr;

    if (value == "if")
        token = new Token(value, TOKEN_IF);
    else if (value == "while")
        token = new Token(value, TOKEN_WHILE);
    else if (value == "def")
        token = new Token(value, TOKEN_LET);
    else if (value == "ret")
        token = new Token(value, TOKEN_RETURN);
    else
        token = new Token(value, TOKEN_ID);

    return token;
}

Token *parse_number()
{
    std::string value = "";

    while(isdigit(current))
    {
        value += current;
        next();
    }

    return new Token(value, TOKEN_INT);
}