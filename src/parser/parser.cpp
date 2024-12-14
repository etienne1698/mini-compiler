#include <iostream>
#include "../lexer/lexer.h"
#include "../logger/logger.h"
#include "parser.h"

Parser::Parser(const Lexer &lexer, const Logger &logger) : lexer(lexer), logger(logger) {}

void Parser::parseFunc()
{
    int token = lexer.getNextToken();
    if (token != TOKEN_IDENTIFIER)
    {
        logger.error("Expected identifier");
    }

    const std::string fnName = lexer.getIdentifier();
    
    if (token = lexer.getNextToken() != '(')
    {
        logger.error("Expected \"(\"");
    }
}

void Parser::parse()
{
    int token;
    while (true)
    {
        token = lexer.getNextToken();
        switch (token)
        {
        case TOKEN_EOF:
            std::cout << "END OF FILE" << "\n";
            return;
        case TOKEN_DEF:
            parseFunc();
            break;
        case TOKEN_IDENTIFIER:
            std::cout << lexer.getIdentifier() << "\n";
            break;
        default:
            return;
        }
    }
}