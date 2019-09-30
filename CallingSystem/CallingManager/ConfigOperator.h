﻿#ifndef CONFIGOPERATOR_H
#define CONFIGOPERATOR_H

/**
* @projectName   CallingSystem
* @brief         配置文件操作类
* @author        SuiJiaqi
* @date          2019-09-27
*/

#include <string>
using namespace std;

enum ConfigKey{
    IP,
    PORT,
    HOME,
    VERSION
};

enum LogType
{
	Process,
	InputMsg,
	OutputMsg,
	Error
};

class ConfigOperator
{
public:
    ConfigOperator();

    static bool getConfigValue(ConfigKey key,std::string &sValue);
    static std::string getFilePath();

private:
    static string getConfigKeyStr(ConfigKey key);
};

#endif // CONFIGOPERATOR_H
