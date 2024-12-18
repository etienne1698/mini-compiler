# CPP on windows
```
https://learn.microsoft.com/en-us/cpp/build/walkthrough-compiling-a-native-cpp-program-on-the-command-line?view=msvc-170
```

# Compile
run
```
cl /W4 /EHsc src/main.cpp src/lexer/lexer.cpp src/parser/parser.cpp src/ast/expressions/expr_ast.cpp src/ast/expressions/binaryexpr_ast.cpp src/ast/expressions/callexpr_ast.cpp src/ast/expressions/numberexpr_ast.cpp src/ast/expressions/variableexpr_ast.cpp src/ast/statements/statement_ast.cpp src/ast/statements/prototypestat_ast.cpp /link /out:compile.exe
```