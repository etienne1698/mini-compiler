#include <string>
#include <cctype>

#include "lexer.h"

Lexer::Lexer(const std::string &input) : source(input) {}

char Lexer::getNextChar()
{
    if (position < source.size())
    {
        return source[position++];
    }
    return '\0';
}

TOKEN Lexer::getNextToken()
{
    char lastChar = getNextChar();

    while (isspace(lastChar))
    {
        lastChar = getNextChar();
    }

    if (isalpha(lastChar))
    {
        identifierStr = lastChar;
        while (isalnum(lastChar = getNextChar()))
        {
            identifierStr += lastChar;
        }
        if (identifierStr == "func")
        {
            return TOKEN_FUNC;
        }
        return TOKEN_IDENTIFIER;
    }
    return TOKEN_EOF;
}

std::string Lexer::getIdentifier()
{
    return identifierStr;
}