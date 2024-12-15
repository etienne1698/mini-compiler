#include <iostream>
#include "lexer/lexer.h"
#include "parser/parser.h"

using namespace std;

int main()
{
    Lexer lexer = Lexer("1 + 1");
    Parser parser = Parser(lexer);
    parser.parse();

    return 0;
}