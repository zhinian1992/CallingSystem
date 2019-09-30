#pragma once

enum class CallbackType
{
	Get_Org_Data = 5000,
	Connect_Failed = 5002,
	Connect_Succeed = 5001,
	Get_Org_Data_Failed = 5003,

	Logging = 6000,
	Log_Succeed = 6001,
	Log_Failed = 6002,
	Logout = 6003,
	
	Call_Succeed = 7000,
	Call_Failed = 7001,
	Skip_Succeed = 7002,
	Skip_Failed = 7003,
	Treated_Succeed = 7004,
	Treated_Failed = 7005,

	Get_Queue_Succeed = 8001,
	Get_Queue_Failed = 8002,
	Queue_Refresh = 8003,
	Queue_Add = 8004,
	Queue_Remove = 8005,
	
};