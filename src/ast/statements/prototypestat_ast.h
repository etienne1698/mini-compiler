#include <iostream>
#include <vector>
#include "./statement_ast.h"

#ifndef PROTOTYPESTAT_AST_H
#define PROTOTYPESTAT_AST_H

class PrototypeStatementAST  : public StatementAST
{
    std::string name;
    std::vector<std::string> args;

public:
    PrototypeStatementAST(const std::string &name, std::vector<std::string> args);

    const std::string &getName();
};

#endif