#pragma once
#include <memory>
#include <map>
#include <functional>
#include "CallbackType.h"

class ServerConnection;
class CallingManager
{
public:
	static CallingManager* getInstance();

	~CallingManager();

	void Connect();

	void SendMessage(std::string msg);

	void ConnectErrorCallback();

	void MessageReceiveCallback(std::string msg);

	void SetCallback(CallbackType type, std::function<void(std::string)> func);

private:
	CallingManager();

	void InitCallbackMap();

	CallbackType GetReceiveMsgType(std::string msg);

private:
	static CallingManager* m_pManager;
	std::shared_ptr<ServerConnection> m_pConnect;
	std::map<CallbackType, std::function<void(std::string)>> m_CbMap;
};

