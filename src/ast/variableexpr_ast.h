#include <iostream>
#include "./expr_ast.h"

#ifndef VARIABLEEXPR_AST_H
#define VARIABLEEXPR_AST_H

class VariableExprAST : public ExprAST
{
    std::string name;

public:
    VariableExprAST(std::string &name);
};

#endif