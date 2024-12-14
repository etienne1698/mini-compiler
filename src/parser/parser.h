#include "../lexer/lexer.h"

#include "../ast/expr_ast.h"
#include "../ast/numberexpr_ast.h"
#include "../ast/variableexpr_ast.h"
#include "../ast/callexpr_ast.h"
#include "../ast/binaryexpr_ast.h"
#include "../ast/prototypeexpr_ast.cpp"

#ifndef PARSER_H
#define PARSER_H

class Parser
{
    Lexer lexer;
    std::unique_ptr<ExprAST> parseFunc();
    std::unique_ptr<ExprAST> logError(std::string err);
    int currentToken;
    void getNextToken();

public:
    explicit Parser(const Lexer &lexer);
    void parse();
    
};

#endif