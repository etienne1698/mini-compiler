# Tuto "Kaleidoscope Langage" 
https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl01.html#id1

# Compile
run
```
cl /W4 /EHsc src/main.cpp src/lexer/lexer.cpp src/parser/parser.cpp src/ast/expr_ast.cpp src/ast/binaryexpr_ast.cpp src/ast/callexpr_ast.cpp src/ast/numberexpr_ast.cpp src/ast/prototypeexpr_ast.cpp src/ast/variableexpr_ast.cpp /link /out:compile.exe
```