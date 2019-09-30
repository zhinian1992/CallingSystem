#ifndef MINIDUMPHANDLER_H
#define MINIDUMPHANDLER_H
#include <Windows.h>
#include "logger.h"

class MiniDumpHandler : public Logger
{
public:
    MiniDumpHandler();

    void CreateMiniDump(EXCEPTION_POINTERS* pep);
};

#endif // MINIDUMPHANDLER_H
