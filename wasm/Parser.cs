using Compiler.Exceptions;

namespace Compiler;

public class Parser
{
    private Tokenizer _tokenizer;
    private Token _token;

    public Parser(Tokenizer tokenizer)
    {
        _tokenizer = tokenizer;
        _token = tokenizer.NextToken();
    }

    private Token? Eat(TokenType type)
    {
        if (_token == null)
            return null;

        if(_token.Type != type)
            throw new UnexpectedTokenException(_token.Type.ToString());

        _token = _tokenizer.NextToken();
        return _token;
    }

    public AbstractSyntaxTree Parse()
    {
        return ParseCompound();
    }

    private AbstractSyntaxTree ParseId()
    {
        var value = _token.Value;
        Eat(TokenType.TOKEN_ID);

        if (value == "sysout")
        {
            return new AbstractSyntaxTree(AbstractSyntaxTreeType.ST_CALL)
            {
                Name = value,
                Value = ParseBlock()
            };
        }

        if (value == "sysin")
        {
            return new AbstractSyntaxTree(AbstractSyntaxTreeType.ST_CALL)
            {
                Name = value,
                Value = ParseBlock()
            };
        }

        if (_token.Type == TokenType.TOKEN_EQUALS)
        {
            Eat(TokenType.TOKEN_EQUALS);
            return new AbstractSyntaxTree(AbstractSyntaxTreeType.ST_ASSIGNMENT)
            {
                Name = value,
                Value = ParseExpression()
            };
        }

        var ast = new AbstractSyntaxTree(AbstractSyntaxTreeType.ST_VARIABLE)
        {
            Name = value
        };

        if(_token.Type == TokenType.TOKEN_LPAREN)
        {
            ast.Type = AbstractSyntaxTreeType.ST_FUNCTION;
            ast.Value = ParseBlock();
        }

        return ast;
    }

    private AbstractSyntaxTree ParseBlock()
    {
        Eat(TokenType.TOKEN_LPAREN);

        var ast = new AbstractSyntaxTree(AbstractSyntaxTreeType.ST_COMPOUND);

        while (_token.Type != TokenType.TOKEN_RPAREN)
            ast.Children.Add(ParseExpression());

        Eat(TokenType.TOKEN_RPAREN);

        if (_token.Type == TokenType.TOKEN_LBRACE)
        {
            ast.Type = AbstractSyntaxTreeType.ST_FUNCTION;
            ast.Value = ParseCompound();
        }
        else
            ast.Type = AbstractSyntaxTreeType.ST_CALL;

        return ast;
    }

    private AbstractSyntaxTree ParseExpression()
    {
        var ast = new AbstractSyntaxTree(AbstractSyntaxTreeType.ST_COMPOUND);

        ast.Children.Add(ParseStatement());

        while(_token.Type == TokenType.TOKEN_COMMA)
        {
            Eat(TokenType.TOKEN_COMMA);
            ast.Children.Add(ParseStatement());
        }

        return ast;
    }

    private AbstractSyntaxTree ParseInt()
    {
        var value = int.Parse(_token.Value);
        Eat(TokenType.TOKEN_NUMBER);

        return new AbstractSyntaxTree(AbstractSyntaxTreeType.ST_INT)
        {
            IntValue = value
        };
    }

    private AbstractSyntaxTree ParseString()
    {
        var value = _token.Value;
        Eat(TokenType.TOKEN_STRING);

        return new AbstractSyntaxTree(AbstractSyntaxTreeType.ST_STRING)
        {
            Name = value
        };
    }

    private AbstractSyntaxTree ParseIf()
    {
        return new AbstractSyntaxTree(AbstractSyntaxTreeType.ST_NOOP);
    }

    private AbstractSyntaxTree ParseReturn()
    {
        Eat(TokenType.TOKEN_RETURN);

        return new AbstractSyntaxTree(AbstractSyntaxTreeType.ST_CALL)
        {
            Name = "ret",
            Value = ParseExpression()
        };
    }

    private AbstractSyntaxTree ParseDefinition()
    {
        Eat(TokenType.TOKEN_VAR);
        return ParseId();
    }

    private AbstractSyntaxTree ParseStatement()
    {
        return _token.Type switch
        {
            TokenType.TOKEN_ID => ParseId(),
            TokenType.TOKEN_LPAREN => ParseBlock(),
            TokenType.TOKEN_NUMBER => ParseInt(),
            TokenType.TOKEN_IF => ParseIf(),
            TokenType.TOKEN_RETURN => ParseReturn(),
            TokenType.TOKEN_VAR => ParseDefinition(),
            TokenType.TOKEN_STRING => ParseString(),
            _ => throw new UnexpectedTokenException(_token.Type.ToString()),
        };
    }

    private AbstractSyntaxTree ParseCompound()
    {
        //Eat(TokenType.TOKEN_FUN);
        var shouldClose = false;

        if(_token.Type == TokenType.TOKEN_LBRACE)
        {
            Eat(TokenType.TOKEN_LBRACE);
            shouldClose = true;
        }

        var compound = new AbstractSyntaxTree(AbstractSyntaxTreeType.ST_COMPOUND);

        while (_token.Type != TokenType.TOKEN_EOF && _token.Type != TokenType.TOKEN_RBRACE)
        {
            compound.Children.Add(ParseStatement());

            if (_token.Type == TokenType.TOKEN_SEMICOLON)
                Eat(TokenType.TOKEN_SEMICOLON);
        }

        if (shouldClose)
            Eat(TokenType.TOKEN_RBRACE);

        return compound;
    }
}
