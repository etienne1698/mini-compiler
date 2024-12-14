#include "./expr_ast.h"

#ifndef NUMBEREXPR_AST_H
#define NUMBEREXPR_AST_H

class NumberExprAST : public ExprAST
{
  double val;

public:
  NumberExprAST(double Val);
};

#endif