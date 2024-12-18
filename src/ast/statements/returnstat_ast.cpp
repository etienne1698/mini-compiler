#include "./returnstat_ast.h"

ReturnStatementAST::ReturnStatementAST(std::unique_ptr<ExprAST> returnExpr) : returnExpr(std::move(returnExpr)) {};