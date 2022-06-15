namespace Compiler;

public static class FileHandler
{
    public static void WriteFile(string filename, string content)
    {
        using var sw = new StreamWriter(filename);
        sw.WriteLine(content);
    }

    public static string ReadFile(string filename)
    {
        using var sr = new StreamReader(filename);
        var str = sr.ReadToEnd();
        str += "\0";
        return str;
    }
}
