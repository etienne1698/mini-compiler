#include <iostream>

#ifndef LOGGER_H
#define LOGGER_H

class Logger
{

public:
    Logger();
    void error(std::string err);
};

#endif