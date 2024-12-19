#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>

#include "lexer/lexer.h"
#include "parser/parser.h"

using namespace std;


string getFileContent(string fileName)
{
    ifstream inFile;
    inFile.open(fileName);

    stringstream strStream;
    strStream << inFile.rdbuf();
    return strStream.str();
}

int main()
{
    Lexer lexer = Lexer(getFileContent("./test.cm"));
    Parser parser = Parser(lexer);
    parser.parse();

    return 0;
}