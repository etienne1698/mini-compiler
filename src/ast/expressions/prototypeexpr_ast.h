#include <iostream>
#include <vector>
#include "./expr_ast.h"

#ifndef PROTOTYPEEXPR_AST_H
#define PROTOTYPEEXPR_AST_H

class PrototypeAST
{
    std::string name;
    std::vector<std::string> args;

public:
    PrototypeAST(const std::string &name, std::vector<std::string> args);

    const std::string &getName();
};

#endif