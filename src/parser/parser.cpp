#include <iostream>
#include "../lexer/lexer.h"
#include "../logger/logger.h"
#include "parser.h"

Parser::Parser(const Lexer &lexer, const Logger &logger) : lexer(lexer), logger(logger) {}

void Parser::parseFunc()
{
    TOKEN token = lexer.getNextToken();
    if (token != TOKEN_IDENTIFIER)
    {   
        logger.error("Expected identifier");
    }
}

void Parser::parse()
{
    TOKEN token;
    while (true)
    {
        token = lexer.getNextToken();
        switch (token)
        {
        case TOKEN_EOF:
            std::cout << "END OF FILE" << "\n";
            return;
        case TOKEN_FUNC:
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