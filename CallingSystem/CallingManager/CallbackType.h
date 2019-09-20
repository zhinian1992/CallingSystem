#pragma once

enum class CallbackType
{
	Connecting = 1000,
	Connect_Failed = 1001,
	Connect_Succeed = 1002,

	Logging = 2000,
	Log_Succeed = 2001,
	Log_Failed = 2002,
	Logout = 2003,
	
	Get_Queue_Succeed = 3000,
	Get_Queue_Failed = 3001,
	Queue_Refresh = 3002,
	Queue_Add = 3003,
	Queue_Remove = 3004,

	Call_Succeed = 4000,
	Call_Failed = 4001,
	Skip_Succeed = 4002,
	Skip_Failed = 4003,
	Treated_Succeed = 4004,
	Treated_Failed = 4005,
};