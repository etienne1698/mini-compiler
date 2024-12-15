#include "./binaryexpr_ast.h"

BinaryExprAST::BinaryExprAST(char op, std::unique_ptr<ExprAST> left,
                             std::unique_ptr<ExprAST> right) : op(op), left(std::move(left)), right(std::move(right)) {}