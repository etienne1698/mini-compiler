#include "../lexer/lexer.h"
#include "../logger/logger.h"

#ifndef PARSER_H
#define PARSER_H

class Parser
{
    Lexer lexer;
    Logger logger;
    void parseFunc();

public:
    explicit Parser(const Lexer &lexer, const Logger &logger);
    void parse();
};

#endif