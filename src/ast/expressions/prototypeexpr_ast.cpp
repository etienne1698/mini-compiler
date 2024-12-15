#include "./prototypeexpr_ast.h"
#include <iostream>
#include <vector>

PrototypeAST::PrototypeAST(const std::string &name, std::vector<std::string> args)
    : name(name), args(std::move(args)) {}

const std::string &PrototypeAST::getName() {
    return name;
}