#include <iostream>
#include <vector>
#include "./expr_ast.h"

#ifndef CALLEXPR_AST_H
#define CALLEXPR_AST_H

class CallExprAST : public ExprAST
{
    std::string callee;
    std::vector<std::unique_ptr<ExprAST>> args;

public:
    CallExprAST(std::string callee, std::vector<std::unique_ptr<ExprAST>> args);
};

#endif