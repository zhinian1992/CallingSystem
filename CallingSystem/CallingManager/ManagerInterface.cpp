#include "stdafx.h"
#include "ManagerInterface.h"
#include "CallingManager.h"


MANAGERINTERFACE void ExcuteCommand(std::string cmd)
{
	CallingManager* cm = CallingManager::getInstance();
	if (cmd.compare("connect") == 0) {
		cm->Connect();
	}
	else {
		cm->SendMessage(cmd);
	}
	return;
}

MANAGERINTERFACE void RegisterCallback(void(*callback)(std::string))
{
	CallingManager* cm = CallingManager::getInstance();
	cm->SetCallback(callback);
	return;
}
