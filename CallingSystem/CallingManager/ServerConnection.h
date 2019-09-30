#pragma once
#include <string>
#include <winsock2.h>
#include <functional>
#include <thread>

class ServerConnection
{
public:
	ServerConnection();
	~ServerConnection();

	bool CreateSocket();

	bool CreateConnection();

	void CreateMsgLooping();

	void CloseSocket();

	void HeartbeatLooping();

	bool SendMessage(std::string msg);

	void ReceiveMessage(std::string msg);

	void SetConnectFailed_Callback(std::function<void()> func);

	void SetReceiveMsg_Callback(std::function<void(std::string)> func);

	std::thread heartThread() {
		return std::thread(&ServerConnection::HeartbeatLooping, this);
	}
	std::thread receiveThread() {
		return std::thread(&ServerConnection::CreateMsgLooping, this);
	}

private:
	static ServerConnection* m_pServerConn;
	SOCKET m_SockClient;
	std::string m_ServerIP;
	int m_ServerPort;
	bool m_bConnecting;

	std::function<void(std::string)> m_RecvCallback;
	std::function<void()> m_ConnErrCallback;
};

