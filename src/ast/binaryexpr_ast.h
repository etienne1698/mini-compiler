#include <iostream>
#include "./expr_ast.h"

#ifndef BINARYEXPR_AST_H
#define BINARYEXPR_AST_H

class BinaryExprAST : public ExprAST
{
    char op;
    std::unique_ptr<ExprAST> left, right;

public:
    BinaryExprAST(char op, std::unique_ptr<ExprAST> left,
                  std::unique_ptr<ExprAST> right);
};

#endif