# Tuto "Kaleidoscope Langage" 
https://llvm.org/docs/tutorial/MyFirstLanguageFrontend/LangImpl01.html#id1

# Compile
run
```
cl /W4 /EHsc src/main.cpp src/lexer/lexer.cpp src/parser/parser.cpp src/logger/logger.cpp src/ast/expr_ast.cpp /link /out:compile.exe
```