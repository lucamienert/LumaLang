using Compiler.Types;

namespace Compiler;

public class AbstractSyntaxTree
{
    public AbstractSyntaxTreeType Type { get; set; }
    public List<AbstractSyntaxTree> Children { get; set; }
    public AbstractSyntaxTree Value { get; set; }
    public string Name { get; set; }
    public int IntValue{ get; set; }
    public int DataValue { get; set; }

    public AbstractSyntaxTree(AbstractSyntaxTreeType type)
    {
        Type = type;

        if (type == AbstractSyntaxTreeType.ST_COMPOUND)
            Children = new List<AbstractSyntaxTree>();
    }
}
