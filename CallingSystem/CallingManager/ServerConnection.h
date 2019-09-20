#pragma once
#include <string>
#include <winsock2.h>
#include <functional>

class ServerConnection
{
public:
	ServerConnection();
	~ServerConnection();

	bool CreateSocket();

	bool CreateConnection();

	static void CreateMsgLooping();

	void CloseSocket();

	static void HeartbeatLooping();

	bool SendMessage(std::string msg);

	void ReceiveMessage(std::string msg);

	void SetConnectFailed_Callback(std::function<void()> func);

	void SetReceiveMsg_Callback(std::function<void(std::string)> func);

private:
	static ServerConnection* m_pServerConn;
	SOCKET m_SockClient;
	std::string m_ServerIP;
	int m_ServerPort;
	bool m_bConnecting;

	std::function<void(std::string)> m_RecvCallback;
	std::function<void()> m_ConnErrCallback;
};

