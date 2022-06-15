using System.Runtime.Serialization;

namespace Compiler.Exceptions;

public class UnexpectedTokenException : Exception
{
    public UnexpectedTokenException() : base("Unexpected Token!") {}
    public UnexpectedTokenException(string message) : base(message) { }
    public UnexpectedTokenException(Token token) : base($"Unexpected Token: {token.Value}") { }
    public UnexpectedTokenException(SerializationInfo info, StreamingContext context) : base(info, context) { }
}