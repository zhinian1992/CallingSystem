#include "logger.h"
#include <Windows.h>

Logger::Logger()
{

}

void Logger::writeDebugLog(const std::string desc, const std::string log)
{
    OutputDebugStringA(desc.c_str());
    OutputDebugStringA(log.c_str());
    OutputDebugStringA("\n");
}
