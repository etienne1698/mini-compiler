#include <iostream>
#include <vector>
#include "./statement_ast.h"

#ifndef PROTOTYPE_AST_H
#define PROTOTYPEAST_H

class PrototypeAST  : public StatementAST
{
    std::string name;
    std::vector<std::string> args;

public:
    PrototypeAST(const std::string &name, std::vector<std::string> args);

    const std::string &getName();
};

#endif