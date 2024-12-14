#include <iostream>
#include "../lexer/lexer.h"

#include "../ast/expr_ast.h"
#include "../ast/numberexpr_ast.h"
#include "../ast/variableexpr_ast.h"
#include "../ast/callexpr_ast.h"
#include "../ast/binaryexpr_ast.h"
#include "../ast/prototypeexpr_ast.cpp"

#include "parser.h"

Parser::Parser(const Lexer &lexer) : lexer(lexer) {}

void Parser::getNextToken()
{
    currentToken = lexer.getNextToken();
}

std::unique_ptr<ExprAST> Parser::parseFunc()
{
    getNextToken();
    if (currentToken != TOKEN_IDENTIFIER)
    {
        return logError("Expected identifier");
    }
    const std::string fnName = lexer.getIdentifier();
    getNextToken();
    if (currentToken != '(')
    {
        return logError("Expected \"(\"");
    }
    do {
        getNextToken();
        if (currentToken != TOKEN_IDENTIFIER && currentToken != TOKEN_NUMBER) {
            return logError("Expected identifier or number");
        }
    } while(currentToken == ',');
}

void Parser::parse()
{
    while (true)
    {
        getNextToken();
        switch (currentToken)
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

std::unique_ptr<ExprAST> Parser::logError(std::string err)
{
    std::cout << "\033[31;1;4m" << err << "\033[0m" << "\n";
    return nullptr;
}