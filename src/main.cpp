#include <iostream>
#include "lexer/lexer.h"
#include "parser/parser.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::string getFileContent(std::string fileName)
{
    std::ifstream inFile;
    inFile.open(fileName);

    std::stringstream strStream;
    strStream << inFile.rdbuf();
    return strStream.str();
}

using namespace std;

int main()
{
    Lexer lexer = Lexer(getFileContent("./test.cm"));
    Parser parser = Parser(lexer);
    parser.parse();

    return 0;
}