#include "pch.h"
#include "../CallingManager/ManagerInterface.h"
#include <string>

void testdll(std::string s) {
	int a = 0;
}

TEST(ManagerInterface, RegisterCallbackTest) {
	RegisterCallback(testdll);
	ExcuteCommand("connect");
	//EXPECT_TRUE(m_pServerConn->CreateSocket());
}