#include "ConfigOperator.h"
#include <Windows.h>
#include <WinBase.h>
#include <direct.h>
#include <ctime>
#include <fstream>
#include <objbase.h>
#include <QDebug>

#define CONFIGFILEPATH "/config.ini"
#define CONFIGSEGMENT "CallingSystem"
#define RETURNSTRINGSIZE 32

ConfigOperator::ConfigOperator()
{
	
}

bool ConfigOperator::getConfigValue(ConfigKey key, QString &sValue)
{
    std::string sKey = getConfigKeyStr(key);
    if(sKey.empty())
    {
        sValue = QStringLiteral("配置文件字段不存在");
        return false;
    }
    else
    {
        string sFilePath = getFilePath().toStdString();
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
            sValue = QString::number(error);
            return false;
        }
        else
        {
            string str = cValue;
            sValue = QString::fromStdString(str);
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

QString ConfigOperator::getFilePath()
{
    char cPath[128] = {0};
    _getcwd(cPath, sizeof(cPath));
    string sFilePath = cPath;
    return QString::fromStdString(sFilePath);
}

