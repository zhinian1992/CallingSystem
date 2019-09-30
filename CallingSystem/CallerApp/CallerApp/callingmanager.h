#ifndef CALLINGMANAGER_H
#define CALLINGMANAGER_H

#include <QObject>
#include <Windows.h>
#include <functional>
#include "logger.h"

typedef void(_stdcall *ExcuteCommand)(std::string);
typedef void(_stdcall *RegisterCallback)(void (*callback)(std::string));


class CallingManager : public QObject,
        Logger
{
    Q_OBJECT
public:
    explicit CallingManager(QObject *parent = nullptr);

    bool loadManagerDLL();
    void excuteCommand(std::string request);
    void receiveCallback(std::string info);

signals:
    void receive(QString);
public slots:

private:
    HMODULE m_hDll;

    ExcuteCommand fExcute;
    RegisterCallback fRegeister;
};

#endif // CALLINGMANAGER_H
