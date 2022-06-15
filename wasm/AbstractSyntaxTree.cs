namespace Compiler;

public enum AbstractSyntaxTreeType
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
    ST_NOOP
}

public class AbstractSyntaxTree
{
    public AbstractSyntaxTreeType Type { get; set; }
    public List<AbstractSyntaxTree> Children { get; set; }
    public string Name { get; set; }
    public AbstractSyntaxTree Value { get; set; }
    public int IntValue{ get; set; }
    public int DataValue { get; set; }

    public AbstractSyntaxTree(AbstractSyntaxTreeType type)
    {
        Type = type;

        if (type == AbstractSyntaxTreeType.ST_COMPOUND)
            Children = new List<AbstractSyntaxTree>();
    }
}
