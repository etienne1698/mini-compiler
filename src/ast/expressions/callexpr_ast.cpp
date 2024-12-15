#include "./callexpr_ast.h"

CallExprAST::CallExprAST(std::string callee, std::vector<std::unique_ptr<ExprAST>> args) : callee(callee), args(std::move(args)) {}