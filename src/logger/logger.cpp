#include <iostream>
#include "logger.h"

Logger::Logger() {}

void Logger::error(std::string err) {
    std::cout << "\033[31;1;4m" << err << "\033[0m" << "\n";
}