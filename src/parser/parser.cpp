#include "parser.h"

using namespace std;

Parser::Parser(const Lexer &lexer) : lexer(lexer)
{
}

map<char, int> Parser::BinopPrecedence = {
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
unique_ptr<ExprAST> Parser::parseIdentifierExpr()
{
    string identifierName = lexer.getIdentifier();
    getNextToken();
    if (currentToken != '(')
    {
        cout << "Parse Variable: " << "\"" << identifierName << "\"" << "\n";
        return make_unique<VariableExprAST>(identifierName);
    }
    vector<unique_ptr<ExprAST>> args;
    while (true)
    {
        if (auto arg = parseExpr())
            args.push_back(move(arg));
        else
            return nullptr;
        if (currentToken == ')')
            break;
        if (currentToken != ',')
            return logError("Expected ')' or ',' in argument list");
        getNextToken();
    }
    getNextToken();
    cout << "Parse Function Call: " << "\"" << identifierName << "\"" << "\n";
    return make_unique<CallExprAST>(identifierName, move(args));
}

unique_ptr<ExprAST> Parser::parsePrimaryExpr()
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

unique_ptr<ExprAST> Parser::parseExpr()
{
    auto LHS = parsePrimaryExpr();
    if (!LHS)
        return nullptr;
    getNextToken();
    return parseBinOp(0, move(LHS));
}

/**
 * parse:
 * - (1 + 2)
 * - (var)
 * - (fncall())
 * - ...
 */
unique_ptr<ExprAST> Parser::parseParentesisExpr()
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
unique_ptr<ExprAST> Parser::parseNumberExpr()
{
    auto Result = make_unique<NumberExprAST>(lexer.getNumVal());
    cout << "Parse Number: " << lexer.getNumVal() << "\n";
    return move(Result);
}

unique_ptr<StatementAST> Parser::parseFuncDef()
{
    getNextToken();
    if (currentToken != TOKEN_IDENTIFIER)
    {
        logError("Identifier Expected");
        return nullptr;
    }
    string identifierName = lexer.getIdentifier();
    getNextToken();

    if (currentToken != '(')
    {
        logError("Expected '('");
        return nullptr;
    }
    vector<string> args;
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

    cout << "Function def: " << identifierName << "\n";
    return make_unique<PrototypeStatementAST>(identifierName, move(args));
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

unique_ptr<ExprAST> Parser::logError(string err)
{
    cout << "\033[31;1;4m" << err << "\033[0m" << "\n";
    return nullptr;
}

unique_ptr<ExprAST> Parser::parseBinOp(int exprPrec,
                                            unique_ptr<ExprAST> left)
{

    while (true)
    {
        int tokPrec = getTokenPrecedence();
        if (tokPrec < exprPrec)
            return left;

        char op = currentToken;
        getNextToken();
        auto right = parsePrimaryExpr();

        if (!right)
            return nullptr;

        getNextToken();

        int nextTokPrec = getTokenPrecedence();

        if (tokPrec < nextTokPrec)
        {
            right = parseBinOp(tokPrec + 1, move(right));
            if (!right)
                return nullptr;
        }

        cout << "Parsed Binary operation" << "\n";
        left =
            make_unique<BinaryExprAST>(op, move(left), move(right));
    }

    return nullptr;
}