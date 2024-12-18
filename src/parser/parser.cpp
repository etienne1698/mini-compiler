#include <cctype>
#include <string>
#include "memory"

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

/**
 * parse:
 * - fnCall(...args)
 * - variable
 */
std::unique_ptr<ExprAST> Parser::parseIdentifierExpr()
{
    std::string identifierName = lexer.getIdentifier();
    getNextToken();
    if (currentToken != '(')
    {
        return std::make_unique<VariableExprAST>(identifierName);
    }
    std::vector<std::unique_ptr<ExprAST>> args;
    while (true)
    {
        if (auto arg = parseExpr())
            args.push_back(std::move(arg));
        else
            return nullptr;
        if (currentToken == ')')
            break;
        if (currentToken != ',')
            return logError("Expected ')' or ',' in argument list");
        getNextToken();
    }
    getNextToken();

    return std::make_unique<CallExprAST>(identifierName, std::move(args));
}

std::unique_ptr<ExprAST> Parser::parseExpr()
{
    switch (currentToken)
    {
    case TOKEN_IDENTIFIER:
        return parseIdentifierExpr();
    case TOKEN_NUMBER:
        return parseNumberExpr();
    case '(':
        return parseParentesisExpr();
    default:
        return nullptr;
    }
}

/**
 * parse:
 * - (1 + 2)
 * - (var)
 * - (fncall())
 * - ...
 */
std::unique_ptr<ExprAST> Parser::parseParentesisExpr()
{
    getNextToken();
    auto V = parseExpr();
    if (!V)
        return nullptr;
    getNextToken();
    if (currentToken != ')')
        return logError("expected ')'");
    getNextToken();
    return V;
}
std::unique_ptr<ExprAST> Parser::parseNumberExpr()
{
    auto Result = std::make_unique<NumberExprAST>(lexer.getNumVal());
    return std::move(Result);
}

std::unique_ptr<StatementAST> Parser::parseFuncDef()
{
    getNextToken();
    if (currentToken != TOKEN_IDENTIFIER)
    {
        logError("Identifier Expected");
        return nullptr;
    }
    std::string identifierName = lexer.getIdentifier();
    getNextToken();
    
    if (currentToken != '(')
    {
        logError("Expected '('");
        return nullptr;
    }
    std::vector<std::string> args;
    while (true)
    {
        getNextToken();
        if (currentToken == ')')
        {
            break;
        }
        if (currentToken != TOKEN_IDENTIFIER)
        {
            logError("Identifier Expected");
            return nullptr;
        }
        args.push_back(lexer.getIdentifier());
    }

    std::cout << "Function def: " << identifierName; 
    return std::make_unique<PrototypeAST>(identifierName, std::move(args));
}

void Parser::parse()
{
    while (true)
    {
        getNextToken();
        switch (currentToken)
        {
        case TOKEN_EOF:
            return;
        case TOKEN_DEF:
            parseFuncDef();
            break;
        default:
            parseExpr();
            break;
        }
    }
}

std::unique_ptr<ExprAST> Parser::logError(std::string err)
{
    std::cout << "\033[31;1;4m" << err << "\033[0m" << "\n";
    return nullptr;
}