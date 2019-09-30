#include "callingmanager.h"
#include <string>
#include <assert.h>
#include <QDebug>

using namespace std;

CallingManager* m_callingMgr = NULL;

CallingManager::CallingManager(QObject *parent) : QObject(parent)
{
    m_callingMgr = this;
}

///
/// \brief CallingManager::loadManagerDLL 加载CallingManager.dll
/// \return 返回false 加载失败
///
bool CallingManager::loadManagerDLL()
{
    string path = "CallingManager.dll";
    m_hDll = LoadLibraryA(path.c_str());
    if (m_hDll == NULL)
    {
        DWORD iError = GetLastError();
        writeDebugLog("load CallingManager failed!", "the error code is:" + to_string(iError));
        return false;
    }
    else
    {
        fExcute = (ExcuteCommand)::GetProcAddress(m_hDll, "ExcuteCommand");
        fRegeister = (RegisterCallback)::GetProcAddress(m_hDll, "RegisterCallback");

        if (fExcute == NULL || fRegeister == NULL)
        {
            DWORD iError = GetLastError();
            writeDebugLog("load CallingManager method failed!", "the error code is:" + to_string(iError));
            return false;
        }
    }

    /* regeister callback */
    fRegeister([](string str){ m_callingMgr->receiveCallback(str); });

    return true;
}

///
/// \brief CallingManager::excuteCommand 调用CallingManager.dll ExcuteCommand方法
/// \param request 请求参数
///
void CallingManager::excuteCommand(string request)
{
    assert(fExcute);
    fExcute(request);
}

///
/// \brief CallingManager::receiveCallback 注册CallingManager.dll回调 发送接收信号
/// \param info 接受信息
///
void CallingManager::receiveCallback(string info)
{
    emit receive(QString::fromStdString(info));
}
