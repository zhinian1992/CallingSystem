#pragma once

#include <string>
#include "CallbackType.h"

#ifdef MANAGERINTERFACE
#else
#define MANAGERINTERFACE extern"C" __declspec(dllexport)
#endif


MANAGERINTERFACE void ExcuteCommand(std::string cmd);

MANAGERINTERFACE void RegisterCallback(CallbackType type,void (*callback)(std::string));