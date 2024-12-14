#ifndef LEXER_H
#define LEXER_H

enum TOKEN
{
    TOKEN_EOF = -1,
    TOKEN_DEF = -2,
    TOKEN_IDENTIFIER = -3,
    TOKEN_NUMBER = -4,
};

class Lexer
{
    std::string source;
    double numVal;
    std::string identifierStr;
    size_t position = 0;
    char getNextChar();

public:
    explicit Lexer(const std::string &input);
    int getNextToken();
    std::string getIdentifier();
};

#endif