using Compiler;

var arguments = Environment.GetCommandLineArgs();

var file = arguments[1];

var input = FileHandler.ReadFile(file);
var tokenizer = new Tokenizer(input);
var parser = new Parser(tokenizer);
var root = parser.Parse();
var codegen = new CodeGenerator();

var res = codegen.FRoot(root);

FileHandler.WriteFile(arguments[2], res);