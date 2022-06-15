using System.Runtime.Serialization;

namespace Compiler.Exceptions;

public class UnexpectedCharacterException : Exception
{
    public UnexpectedCharacterException() : base("Unexpected Character!") { }
    public UnexpectedCharacterException(string message) : base(message) { }
    public UnexpectedCharacterException(SerializationInfo info, StreamingContext context) : base(info, context) { }
}