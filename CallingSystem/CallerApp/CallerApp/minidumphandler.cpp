#include "minidumphandler.h"
#include <QString>
#include <dbghelp.h>
#include <assert.h>
#include <QString>
#include <time.h>

#pragma comment(lib, "dbghelp.lib")


MiniDumpHandler::MiniDumpHandler()
{

}

void MiniDumpHandler::CreateMiniDump(EXCEPTION_POINTERS *pep)
{
    std::string system_user_name;

    //system user name
    char buffer[256] ={0};
    DWORD dwSize = 256;
    bool bRet = ::GetUserNameA(buffer,&dwSize);
    if(bRet){
        system_user_name = buffer;
    }

    //system time
    time_t timep;
    time (&timep);
    char cTime[32];
    strftime(cTime, sizeof(cTime), "%Y%m%d",localtime(&timep));

    //random number
    int num = rand()%1000;
    QString qNum = QString::number(num);

    std::string fileName = system_user_name;
    fileName.append("_");
    fileName.append(cTime);
    fileName.append("_");
    fileName.append(qNum.toStdString());


    writeDebugLog("enter->","CreateMiniDump");
    std::string sPath = "dump/";
    sPath.append(fileName);
    sPath.append(".dmp");
    writeDebugLog("CreateMiniDump dump file path->",sPath.c_str());

    HANDLE hFile = CreateFileA(sPath.c_str(),
        GENERIC_WRITE,
        0,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL);

    assert(hFile != NULL);
    assert(hFile != INVALID_HANDLE_VALUE);
    if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
    {
        MINIDUMP_EXCEPTION_INFORMATION mdei;

        mdei.ThreadId = GetCurrentThreadId();

        mdei.ExceptionPointers = pep;

        mdei.ClientPointers = FALSE;

        MiniDumpWriteDump(GetCurrentProcess(),
            GetCurrentProcessId(),
            hFile,
            MiniDumpNormal,
            &mdei,
            NULL,
            NULL);

        CloseHandle(hFile);
    }
}
