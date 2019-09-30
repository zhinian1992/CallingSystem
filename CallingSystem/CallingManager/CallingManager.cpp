#include "stdafx.h"
#include "CallingManager.h"
#include "ServerConnection.h"


CallingManager* CallingManager::m_pManager = NULL;

CallingManager * CallingManager::getInstance()
{
	if (m_pManager == NULL)
		m_pManager = new CallingManager();
	return m_pManager;
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

CallingManager::~CallingManager()
{
	delete m_pManager;

	m_pManager = NULL;
}

void CallingManager::Connect()
{
	bool bState = m_pConnect->CreateConnection();
	if (bState)
		m_RecvCallback("{\"type\":1001}");
	else
		m_RecvCallback("{\"type\":1002}");
}

void CallingManager::SendMessage(std::string msg)
{
	m_pConnect->SendMessage(msg);
}

void CallingManager::ConnectErrorCallback()
{
	assert(m_RecvCallback);
	m_RecvCallback("{\"type\":1002}");
}

void CallingManager::MessageReceiveCallback(std::string msg)
{
	assert(m_RecvCallback);
	m_RecvCallback(msg);
}

void CallingManager::SetCallback(std::function<void(std::string)> func)
{
	m_RecvCallback = func;
}
