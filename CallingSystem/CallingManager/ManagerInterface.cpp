#include "stdafx.h"
#include "ManagerInterface.h"
#include "CallingManager.h"


MANAGERINTERFACE void ExcuteCommand(std::string cmd)
{
	CallingManager* cm = CallingManager::getInstance();
	std::string type = "";
	if (type.compare("connect") == 0) {
		cm->Connect();
	}
	else {
		cm->SendMessage(cmd);
	}
	return;
}


MANAGERINTERFACE void RegisterCallback(CallbackType type, void(*callback)(std::string))
{
	CallingManager* cm = CallingManager::getInstance();
	cm->SetCallback(type,callback);
	return;
}
