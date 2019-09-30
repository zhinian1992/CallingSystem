#include "V8handler.h"
#include <Windows.h>
#include <assert.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QSettings>
#include <io.h>

#define HKEY_CURRENT_USER_TCMP "HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"

MyV8Handler::MyV8Handler(CefRefPtr<CefFrame> frame)
{
}

MyV8Handler::~MyV8Handler()
{

}

bool MyV8Handler::Execute(const CefString& name,
	CefRefPtr<CefV8Value> object,
	const CefV8ValueList& arguments,
	CefRefPtr<CefV8Value>& retval,
	CefString& exception) {

	if (name == "test") 
	{
		retval = CefV8Value::CreateString("test success!");
		return true;
	}

    else if (name == "ExcuteCommand")
    {
        OutputDebugStringA("ExcuteCommand");

        if(arguments.size() != 1 || !arguments[0]->IsString()){
            retval = CefV8Value::CreateBool(false);
            return true;
        }
        string sInfo = arguments[0]->GetStringValue();
        HWND hBrowser = FindWindow(NULL, L"叫号器");

        COPYDATASTRUCT cpd;
        cpd.dwData = 0;
        cpd.cbData = sInfo.length();
        cpd.lpData = (PVOID)sInfo.c_str();
        ::SendMessage(hBrowser,WM_COPYDATA, 1000,(LPARAM)&cpd);
        retval = CefV8Value::CreateBool(true);
        return true;
    }

    else if (name == "RegisterCallback")
    {
        OutputDebugStringA("RegisterCallback");

        if(arguments.size() != 1 || !arguments[0]->IsString()){
            retval = CefV8Value::CreateBool(false);
            return true;
        }
        string sInfo = arguments[0]->GetStringValue();
        HWND hBrowser = FindWindow(NULL, L"叫号器");

        COPYDATASTRUCT cpd;
        cpd.dwData = 0;
        cpd.cbData = sInfo.length();
        cpd.lpData = (PVOID)sInfo.c_str();
        ::SendMessage(hBrowser,WM_COPYDATA, 1001,(LPARAM)&cpd);
        retval = CefV8Value::CreateBool(true);
        return true;
    }

    else if (name == "ResizeBrowser")
    {
        OutputDebugStringA("ResizeBrowser");

        if(arguments.size() != 1 || !arguments[0]->IsString()){
            retval = CefV8Value::CreateBool(false);
            return true;
        }
        string sInfo = arguments[0]->GetStringValue();
        HWND hBrowser = FindWindow(NULL, L"叫号器");

        COPYDATASTRUCT cpd;
        cpd.dwData = 0;
        cpd.cbData = sInfo.length();
        cpd.lpData = (PVOID)sInfo.c_str();
        ::SendMessage(hBrowser,WM_COPYDATA, 1002,(LPARAM)&cpd);
        retval = CefV8Value::CreateBool(true);
        return true;
    }
	return false;
}


