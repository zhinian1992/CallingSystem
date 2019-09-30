#ifndef LOGGER_H
#define LOGGER_H
#include <string>

class Logger
{
public:
    Logger();

    static void writeDebugLog(const std::string desc,const std::string log);
};

#endif // LOGGER_H
