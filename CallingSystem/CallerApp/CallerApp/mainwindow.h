#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDialog>
#include "CEF/CefHandler.h"
#include "callingmanager.h"
#include "logger.h"
#include <map>

namespace Ui {
class MainWindow;
}

class MainWindow : public QDialog,
        Logger
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    virtual void resizeEvent(QResizeEvent *event)Q_DECL_OVERRIDE;
    virtual bool nativeEvent(const QByteArray &eventType, void *message, long *result) Q_DECL_OVERRIDE;

private:
    void initBrowser(std::string url);
    void callJSMethod(QString data);

private:
    Ui::MainWindow *ui;
    std::map<int,std::string> m_CallbackMap;

    CefRefPtr<CCefHandler> m_handler;
    CallingManager m_CallMgr;

};

#endif // MAINWINDOW_H
