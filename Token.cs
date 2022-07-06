using Compiler.Types;

namespace Compiler;

public class Token
{
    public TokenType Type { get; private set; }
    public string Value { get; private set; }

    public Token(string value, TokenType type)
    {
        Value = value;
        Type = type;
    }
}
