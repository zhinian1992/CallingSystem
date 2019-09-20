#include "stdafx.h"
#include "CallingManager.h"
#include "ServerConnection.h"


CallingManager* CallingManager::m_pManager = NULL;

CallingManager * CallingManager::getInstance()
{
	if (m_pManager == NULL)
		m_pManager = new CallingManager();
	return nullptr;
}

CallingManager::CallingManager()
{
	m_pConnect = std::make_shared<ServerConnection>();

	m_pConnect->SetConnectFailed_Callback(std::bind(&CallingManager::ConnectErrorCallback, this));
	m_pConnect->SetReceiveMsg_Callback(std::bind(&CallingManager::MessageReceiveCallback, this, std::placeholders::_1));

	assert(m_pConnect);

	bool bState = true;
	bState = m_pConnect->CreateSocket();
	assert(bState);
}

void CallingManager::InitCallbackMap()
{
}

CallbackType CallingManager::GetReceiveMsgType(std::string msg)
{
	return CallbackType::Call_Failed;
}


CallingManager::~CallingManager()
{
	delete m_pManager;

	m_pManager = NULL;
}

void CallingManager::Connect()
{
	bool bState = m_pConnect->CreateConnection();
	if (bState)
		m_CbMap[CallbackType::Connect_Succeed]("");
}

void CallingManager::SendMessage(std::string msg)
{
	m_pConnect->SendMessage(msg);
}

void CallingManager::ConnectErrorCallback()
{
	assert(m_CbMap[CallbackType::Connect_Failed]);
	m_CbMap[CallbackType::Connect_Failed]("");

	Sleep(5000);
	m_pConnect->CreateConnection();
}

void CallingManager::MessageReceiveCallback(std::string msg)
{
	std::function<void(std::string)> func = m_CbMap[GetReceiveMsgType(msg)];
	if (func)
		func(msg);
}

void CallingManager::SetCallback(CallbackType type, std::function<void(std::string)> func)
{
	m_CbMap[type] = std::move(func);
}
