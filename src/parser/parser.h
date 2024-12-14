#include "../lexer/lexer.h"

#ifndef PARSER_H
#define PARSER_H

class Parser
{
    Lexer lexer;
    void parseFunc();

public:
    explicit Parser(const Lexer &lexer);
    void parse();
};

#endif