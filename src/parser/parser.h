#include "../lexer/lexer.h"

#include "../ast/expr_ast.h"
#include "../ast/numberexpr_ast.h"
#include "../ast/variableexpr_ast.h"
#include "../ast/callexpr_ast.h"
#include "../ast/binaryexpr_ast.h"
#include "../ast/prototypeexpr_ast.h"

#ifndef PARSER_H
#define PARSER_H

class Parser
{
    Lexer lexer;
    std::unique_ptr<ExprAST> parseFuncDef();
    std::unique_ptr<ExprAST> parseExpr();
    std::unique_ptr<ExprAST> parseParentesisExpr();
    std::unique_ptr<ExprAST> logError(std::string err);
    char currentToken;
    void getNextToken();
    int getTokenPrecedence();
    static std::map<char, int> BinopPrecedence;

public:
    explicit Parser(const Lexer &lexer);
    void parse();
    
};

#endif