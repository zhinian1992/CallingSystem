#include "stdafx.h"
#include "ServerConnection.h"
#include "ConfigOperator.h"
#include <stdio.h>
#include <future>
#include <thread>
#include <algorithm>
#include <functional>

#pragma comment(lib,"ws2_32.lib")

#define BUF_SIZE 1024*10

ServerConnection* ServerConnection::m_pServerConn;

/// <summary>
/// ��ʼ����������
/// </summary>
/// <param name=""></param>
ServerConnection::ServerConnection()
{
	ConfigOperator::getConfigValue(IP, m_ServerIP);
	string sPort;
	ConfigOperator::getConfigValue(PORT, sPort);
	m_ServerPort = atoi(sPort.c_str());
	m_pServerConn = this;
	m_bConnecting = false;
}


ServerConnection::~ServerConnection()
{
}

/// <summary>
/// ����SocketǶ����
/// </summary>
/// <param name=""></param>
bool ServerConnection::CreateSocket()
{
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;

	wVersionRequested = MAKEWORD(2, 2);

	err = WSAStartup(wVersionRequested, &wsaData);
	if (err != 0) {
		return false;
	}

	m_SockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (m_SockClient == INVALID_SOCKET) {
		WSACleanup();
		return false;
	}

	return true;
}

/// <summary>
/// ����Socket����
/// </summary>
/// <param name=""></param>
bool ServerConnection::CreateConnection()
{
	SOCKADDR_IN addrSrv;
	addrSrv.sin_family = AF_INET;
	addrSrv.sin_addr.S_un.S_addr = inet_addr(m_ServerIP.c_str());
	addrSrv.sin_port = htons(m_ServerPort);
	int iRet = connect(m_SockClient, (SOCKADDR*)&addrSrv, sizeof(SOCKADDR));
	
	if (iRet == SOCKET_ERROR) {
		return false;
	}
	m_bConnecting = true;
	std::thread tHeart = this->heartThread();
	std::thread tReceive = this->receiveThread();
	tReceive.detach();
	tHeart.detach();
	
	return true;
}

/// <summary>
/// ������Ϣѭ����ȡ�����������Ϣ
/// </summary>
/// <param name=""></param>
void ServerConnection::CreateMsgLooping()
{
	while (m_pServerConn->m_bConnecting)
	{
		char recvBuf[BUF_SIZE] = {};
		int nRc = recv(m_pServerConn->m_SockClient, recvBuf, BUF_SIZE, 0);
		if (nRc > 0) {
			std::string msg = recvBuf;
			m_pServerConn->ReceiveMessage(msg);
		}
	}
}

/// <summary>
/// �ر�Socket����
/// </summary>
/// <param name=""></param>
void ServerConnection::CloseSocket()
{
	closesocket(m_SockClient);
	WSACleanup();
}

/// <summary>
/// ��������ѭ����������,���ʱ��5��
/// </summary>
/// <param name=""></param>
void ServerConnection::HeartbeatLooping()
{
	while (m_pServerConn->m_bConnecting) {
		Sleep(5000);

		std::string msg = "{\"type\":1,\"data\":\"alive\"}";
		m_pServerConn->SendMessage(msg);
	}
}

/// <summary>
/// ������Ϣ�������
/// </summary>
/// <param name="msg">��Ϣ����</param>
bool ServerConnection::SendMessage(std::string msg)
{
	msg += "\n";
	int iRet = send(m_SockClient, msg.c_str(), msg.length() + 1, 0);
	if (iRet == SOCKET_ERROR) {
		m_bConnecting = false;
		assert(m_ConnErrCallback);
		m_ConnErrCallback();
		return false;
	}
	return true;
}

/// <summary>
/// ���ܵ��������Ϣ
/// </summary>
/// <param name="msg">��Ϣ����</param>
void ServerConnection::ReceiveMessage(std::string msg)
{
	assert(m_RecvCallback);
	std::string::iterator new_end = remove_if(msg.begin(), msg.end(), std::bind2nd(std::equal_to<char>(), '\n'));
	msg.erase(new_end, msg.end());
	if(msg.compare("{\"msg\":\"success\",\"code\":0,\"data\":\"\",\"type\":1}") != 0)
		m_RecvCallback(msg);
}

/// <summary>
/// �������Ӵ���ص�
/// </summary>
/// <param name=""></param>
void ServerConnection::SetConnectFailed_Callback(std::function<void()> func)
{
	m_ConnErrCallback = std::move(func);
}


/// <summary>
/// ������Ϣ���ܻص�
/// </summary>
/// <param name=""></param>
void ServerConnection::SetReceiveMsg_Callback(std::function<void(std::string)> func)
{
	m_RecvCallback = std::move(func);
}
