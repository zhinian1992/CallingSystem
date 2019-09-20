#include "pch.h"
#include "../CallingManager/ServerConnection.h"
#include <memory>
#include <stdio.h>
#include <Winsock2.h>

#pragma comment(lib, "Ws2_32.lib")
using namespace std;

shared_ptr<ServerConnection> m_pServerConn;


TEST(ServerConnectionTest, CreateSocketTest) {
	m_pServerConn = make_shared<ServerConnection>();
	EXPECT_TRUE(m_pServerConn->CreateSocket());
}

TEST(ServerConnectionTest, CreateConnectionTest) {
	EXPECT_TRUE(m_pServerConn->CreateConnection());
}