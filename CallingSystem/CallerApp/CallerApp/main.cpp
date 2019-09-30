#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include <QApplication>
#include <shlobj.h>
#include <strsafe.h>
#include <string>
#include "CEF/MyCefApp.h"
#include "logger.h"
#include "minidumphandler.h"

#define CLIENT_GUID L"{40F7A096-5A54-4519-90C0-1B818613D7F8}"

///
/// \brief isClientRunning  判断当前客户端是否重复启动
/// \return 返回True 已存在
///
bool isClientRunning(){
    HANDLE hMutex = CreateMutex(NULL, FALSE, CLIENT_GUID);
    assert(hMutex);

    if (ERROR_ALREADY_EXISTS == ::GetLastError())
    {
        QMessageBox::warning(NULL, QString::fromUtf8("错误"),
            QString::fromUtf8("程序已经启动"), QString::fromUtf8("确定"));
        CloseHandle(hMutex);
        hMutex = NULL;
        return true;
    }
    return false;
}

///
/// \brief ExceptionCallBack  崩溃异常回调函数,记录dump文件
/// \return
///
long _stdcall ExceptionCallBack(_EXCEPTION_POINTERS * excp){
    MiniDumpHandler handler;
    handler.CreateMiniDump(excp);

    return EXCEPTION_EXECUTE_HANDLER;
}

///
/// \brief initializeCef 初始化CEF
///
void initializeCef(){
    HINSTANCE hInstance = (HINSTANCE)GetModuleHandle(NULL);
    CefMainArgs main_args(hInstance);
    CefRefPtr<CMyCefApp> app(new CMyCefApp);
    CefExecuteProcess(main_args, app.get(), NULL);
    CefSettings settings;
    CefSettingsTraits::init(&settings);

    TCHAR szSpecialPath[MAX_PATH];
    memset(szSpecialPath, '\0', sizeof(szSpecialPath));
    if (FALSE != SHGetSpecialFolderPath(NULL, szSpecialPath, CSIDL_PROFILE, FALSE))
    {
        StringCbCat(szSpecialPath, sizeof(szSpecialPath), L"\\AppData\\Local\\CallerApp");
        CefString(&settings.cache_path).FromString(szSpecialPath, sizeof(szSpecialPath) / 2, true);
    }

    settings.multi_threaded_message_loop = true;
    settings.ignore_certificate_errors = true;
    settings.log_severity = LOGSEVERITY_DISABLE;
    CefInitialize(main_args, settings, app.get(), NULL);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    initializeCef();

    if(isClientRunning()){
        CefShutdown();
        return a.exit();
    }
    //捕获异常
    SetUnhandledExceptionFilter(ExceptionCallBack);

    MainWindow w;
    w.exec();

    CefShutdown();
    return 0;
}
