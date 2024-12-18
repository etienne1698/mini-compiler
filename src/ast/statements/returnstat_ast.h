#include <iostream>
#include <vector>
#include "./statement_ast.h"
#include "../expressions/expr_ast.h"

#ifndef RETURNSTAT_AST_H
#define RETURNSTAT_AST_H

class ReturnStatementAST : public StatementAST
{
    std::unique_ptr<ExprAST> returnExpr;

public:
    ReturnStatementAST(std::unique_ptr<ExprAST>);
};

#endif