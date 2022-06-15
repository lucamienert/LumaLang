namespace Compiler;

public class CodeGenerator
{
    private string SectionData = ".data\n";
    private string SectionBss = ".bss\n";
    private string Constants = "";

    private int StringCounter = 1;

    public CodeGenerator() {}

    private string FCompund(AbstractSyntaxTree abstractSyntaxTree)
    {
        var value = string.Empty;

        for(var i = 0; i < abstractSyntaxTree.Children.Count; i++)
        {
            var child = abstractSyntaxTree.Children[i];
            var next = F(child);
            value += next;
        }

        return value;
    }

    private string FAssignment(AbstractSyntaxTree abstractSyntaxTree)
    {
        var s = string.Empty;
        var name = abstractSyntaxTree.Name;
        var firstItem = abstractSyntaxTree.Value.Children[0];
        var value = firstItem.Name;

        if(value != string.Empty)
        {
            var assignString = $"{name}_str: .ascii \"{value}\"\n{name}_str_len = .- {name}_str\n";
            SectionData += assignString;
        }
        else
        {
            var intValue = firstItem.IntValue;
            var assignInt = $"{name}: .int {intValue}\n{name}_str: .ascii \"{intValue}\"\n{name}_str_len = .- {name}_str\n";
            SectionData += assignInt;
        }

        return s;
    }

    private string FVariable(AbstractSyntaxTree abstractSyntaxTree)
    {
        var s = "";
        var name = abstractSyntaxTree.Name;
        var declaration = $"{name}: .space {name}_len\n{name}_str: .space {name}_str_len\n";

        SectionBss += declaration;
        Constants += $"{name}_len = 200\n{name}_str_len = 200\n";

        return s;
    }

    private string F(AbstractSyntaxTree abstractSyntaxTree)
    {
        return "";
    }

    public string FRoot(AbstractSyntaxTree abstractSyntaxTree)
    {
        return "";
    }
}
