#include <cctype>
#include <string>

#include "parser.h"

Parser::Parser(const Lexer &lexer) : lexer(lexer)
{
}

std::map<char, int> Parser::BinopPrecedence = {
    {'+', 10},
    {'-', 10},
    {'*', 20},
    {'/', 20}};

void Parser::getNextToken()
{
    currentToken = lexer.getNextToken();
}

int Parser::getTokenPrecedence()
{
    if (!isascii(currentToken))
        return -1;

    // Make sure it's a declared binop.
    int TokPrec = Parser::BinopPrecedence[currentToken];
    if (TokPrec <= 0)
        return -1;
    return TokPrec;
}

std::unique_ptr<ExprAST> Parser::parseExpr()
{
    switch (currentToken)
    {
    case TOKEN_IDENTIFIER:

    default:
        return nullptr;
    }
}

std::unique_ptr<ExprAST> Parser::parseFuncDef()
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
    do
    {
        getNextToken();
        if (currentToken != TOKEN_IDENTIFIER && currentToken != TOKEN_NUMBER)
        {
            return logError("Expected identifier or number");
        }
    } while (currentToken == ',');

    return logError("THIS IS NOT YET FULL IMPLEMENTED");
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
            parseFuncDef();
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