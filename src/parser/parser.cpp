#include <iostream>
#include "../lexer/lexer.h"
#include "parser.h"

Parser::Parser(const Lexer &lexer) : lexer(lexer) {}

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
            std::cout << lexer.getIdentifier() << "\n";
            break;
        case TOKEN_IDENTIFIER:
            std::cout << lexer.getIdentifier() << "\n";
            break;
        default:
            return;
        }
    }
}