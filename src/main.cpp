#include <iostream>
#include "lexer/lexer.h"
#include "parser/parser.h"
#include "logger/logger.h"

using namespace std;

int main()
{
    Lexer lexer = Lexer("func 1");
    Parser parser = Parser(lexer, Logger());
    parser.parse();

    return 0;
}