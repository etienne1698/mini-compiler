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
        std::cout << "Parse Variable: " << "\"" << identifierName << "\"" << "\n";
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
    std::cout << "Parse Function Call: " << "\"" << identifierName << "\"" << "\n";
    return std::make_unique<CallExprAST>(identifierName, std::move(args));
}

std::unique_ptr<ExprAST> Parser::parsePrimaryExpr()
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

std::unique_ptr<ExprAST> Parser::parseExpr()
{
    auto LHS = parsePrimaryExpr();
    if (!LHS)
        return nullptr;
    getNextToken();
    return parseBinOp(0, std::move(LHS));
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
    std::cout << "Parse Number: " << lexer.getNumVal() << "\n";
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

    std::cout << "Function def: " << identifierName << "\n";
    return std::make_unique<PrototypeStatementAST>(identifierName, std::move(args));
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

std::unique_ptr<ExprAST> Parser::parseBinOp(int exprPrec,
                                            std::unique_ptr<ExprAST> left)
{

    while (true)
    {
        int tokPrec = getTokenPrecedence();
        if (tokPrec < exprPrec)
            return left;

        int op = currentToken;
        getNextToken();
        auto right = parsePrimaryExpr();

        if (!right)
            return nullptr;

        getNextToken();

        int nextTokPrec = getTokenPrecedence();

        if (tokPrec < nextTokPrec)
        {
            right = parseBinOp(tokPrec + 1, std::move(right));
            if (!right)
                return nullptr;
        }

        std::cout << "Parsed Binary operation" << "\n";
        left =
            std::make_unique<BinaryExprAST>(op, std::move(left), std::move(right));
    }

    return nullptr;
}