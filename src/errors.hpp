#include <iostream>
#pragma once
void error(const char *message, int type)
{
    std::cerr << "ERROR " << message << " WITH CODE " << type << std::endl;
    std::cin.get();
    exit(-1);
}