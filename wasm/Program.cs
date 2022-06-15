using Compiler;

var file = Environment.GetCommandLineArgs()[1];

var input = FileHandler.ReadFile(file);
var tokenizer = new Tokenizer(input);
var parser = new Parser(tokenizer);
var root = parser.Parse();
var codegen = new CodeGenerator();

var res = codegen.FRoot(root);

FileHandler.WriteFile("test.s", res);