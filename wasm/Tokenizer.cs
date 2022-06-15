using Compiler.Exceptions;

namespace Compiler;

public class Tokenizer
{
    private readonly string _source;
    private readonly int _sourceSize;
    private char _current;
    private int _index;

    public Tokenizer(string source)
    {
        _source = source;
        _index = 0;
        _sourceSize = source.Length;
        _current = source[_index];
    }

    private void Next()
    {
        if (_current != '\0' && _index < _sourceSize)
        {
            _index++;
            _current = _source[_index];
        }
    }

    private void SkipWhitespace()
    {
        if(char.IsWhiteSpace(_current))
            Next();
    }

    private Token? MoveWithToken(Token token)
    {
        if (token == null)
            return null;

        Next();
        return token;
    }

    private Token MoveCurrentType(TokenType type)
    {
        var token = new Token(_current.ToString(), type);
        Next();
        return token;
    }

    public Token NextToken()
    {
        while (_current != '\0')
        {
            SkipWhitespace();

            if (char.IsLetter(_current))
                return ParseId();

            if (char.IsDigit(_current))
                return ParseNumber();

            switch(_current)
            {
                case '(': return MoveCurrentType(TokenType.TOKEN_LPAREN);
                case ')': return MoveCurrentType(TokenType.TOKEN_RPAREN);
                case '{': return MoveCurrentType(TokenType.TOKEN_LBRACE);
                case '}': return MoveCurrentType(TokenType.TOKEN_RBRACE);
                case '+': return MoveCurrentType(TokenType.TOKEN_PLUS);
                case '-': return MoveCurrentType(TokenType.TOKEN_MINUS);
                case '*': return MoveCurrentType(TokenType.TOKEN_STAR);
                case '/': return MoveCurrentType(TokenType.TOKEN_SLASH);
                case '=': return MoveCurrentType(TokenType.TOKEN_EQUALS);
                case ';': return MoveCurrentType(TokenType.TOKEN_SEMICOLON);
                case ':': return MoveCurrentType(TokenType.TOKEN_COLON);
                case ',': return MoveCurrentType(TokenType.TOKEN_COMMA);
                case '"': return ParseId();
                case '\0': break;
                default: throw new UnexpectedCharacterException(); break;
            }
        }

        return new Token("0", TokenType.TOKEN_EOF);
    }

    private Token ParseId()
    {
        var value = string.Empty;

        if (_current == '"')
        {
            Next();

            while (_current != '"')
            {
                value += _current;
                Next();
            }

            Next();
            return new Token(value, TokenType.TOKEN_STRING);
        }

        while (char.IsLetter(_current))
        {
            value += _current;
            Next();
        }

        return value switch
        {
            "if" => new Token(value, TokenType.TOKEN_IF),
            "while" => new Token(value, TokenType.TOKEN_WHILE),
            "var" => new Token(value, TokenType.TOKEN_VAR),
            "fun" => new Token(value, TokenType.TOKEN_FUN),
            "for" => new Token(value, TokenType.TOKEN_FOR),
            "ret" => new Token(value, TokenType.TOKEN_RETURN),
            _ => new Token(value, TokenType.TOKEN_ID),
        };
    }

    private Token ParseNumber()
    {
        var value = string.Empty;

        while(char.IsNumber(_current))
        {
            value += _current;
            Next();
        }

        return new Token(value, TokenType.TOKEN_NUMBER);
    }
}
