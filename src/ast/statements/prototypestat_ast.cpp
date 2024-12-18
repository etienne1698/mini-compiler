#include "./prototypestat_ast.h"
#include <iostream>
#include <vector>

PrototypeStatementAST::PrototypeStatementAST(const std::string &name, std::vector<std::string> args)
    : name(name), args(std::move(args)) {}

const std::string &PrototypeStatementAST::getName() {
    return name;
}