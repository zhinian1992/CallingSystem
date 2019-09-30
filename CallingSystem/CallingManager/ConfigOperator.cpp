#include "stdafx.h"
#include "ConfigOperator.h"
#include <Windows.h>
#include <WinBase.h>
#include <direct.h>
#include <ctime>
#include <fstream>
#include <objbase.h>

#define CONFIGFILEPATH "/config.ini"
#define CONFIGSEGMENT "CallingSystem"
#define RETURNSTRINGSIZE 32

ConfigOperator::ConfigOperator()
{
	
}

bool ConfigOperator::getConfigValue(ConfigKey key, string &sValue)
{
    std::string sKey = getConfigKeyStr(key);
    if(sKey.empty())
    {
        sValue = "配置文件字段不存在";
        return false;
    }
    else
    {
        string sFilePath = getFilePath();
		sFilePath.append(CONFIGFILEPATH);
        char cValue[64] = {};
        DWORD iRet = ::GetPrivateProfileStringA(CONFIGSEGMENT,
                                               sKey.c_str(),
                                               NULL,
                                               cValue,
                                               RETURNSTRINGSIZE,
                                               sFilePath.c_str());
        if(iRet == 0)
        {
            int error = GetLastError();
            sValue = to_string(error);
            return false;
        }
        else
        {
			sValue = cValue;
            return true;
        }
    }
}

string ConfigOperator::getConfigKeyStr(ConfigKey key)
{
    switch (key) {
    case IP:
        return "IP";
        break;
    case PORT:
        return "PORT";
        break;
    case HOME:
        return "HOME";
        break;
    case VERSION:
        return "VERSION";
        break;
    default:
        return "";
        break;
    }
}

string ConfigOperator::getFilePath()
{
    char cPath[128] = {0};
    _getcwd(cPath, sizeof(cPath));
    string sFilePath = cPath;
    return sFilePath;
}

