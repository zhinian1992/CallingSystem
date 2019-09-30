#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ConfigOperator.h"
#include <QResizeEvent>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QMessageBox>
#include <string>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 设置窗体最大化和最小化
    Qt::WindowFlags windowFlag  = Qt::Dialog;
    windowFlag  |= Qt::WindowMinimizeButtonHint;
    windowFlag  |= Qt::WindowMaximizeButtonHint;
    windowFlag  |= Qt::WindowCloseButtonHint;

    setWindowFlags(windowFlag);

    if(!m_CallMgr.loadManagerDLL()){
        QMessageBox::warning(NULL, QString::fromUtf8("错误"),
            QString::fromUtf8("加载CallManager.dll文件失败"), QString::fromUtf8("确定"));
    }
    else{
        connect(&m_CallMgr,&CallingManager::receive,this,&MainWindow::callJSMethod);
        QString url;
        if(!ConfigOperator::getConfigValue(HOME,url)){
            QMessageBox::warning(NULL, QString::fromUtf8("错误"),
                QString::fromUtf8("加载配置config.ini文件失败"), QString::fromUtf8("确定"));
        }
        else
            this->initBrowser(url.toStdString());
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initBrowser(std::string url)
{
    writeDebugLog("call initBrowser url->",url.c_str());

    RECT rect;
    rect.top = this->geometry().top();
    rect.bottom = this->geometry().bottom();
    rect.left = this->geometry().left();
    rect.right = this->geometry().right();

    m_handler = new CCefHandler();
    CefString cstr = url;
    m_handler->CreateBrowser((HWND)this->winId(), rect, cstr);
    this->show();
}


void MainWindow::callJSMethod(QString data)
{
    assert(m_handler);
    qDebug()<<"callJSMethod:"<<data<<endl;

    QJsonParseError jsonerror;
    QJsonDocument doc = QJsonDocument::fromJson(data.toUtf8(), &jsonerror);

    assert(!doc.isNull());
    assert(jsonerror.error == QJsonParseError::NoError);
    assert(doc.isObject());

    QJsonObject obj = doc.object();
    assert(obj.contains("type")
           &&obj.value("type").isDouble());

    int type = obj.value("type").toInt();

    std::string method = this->m_CallbackMap[type];
    qDebug()<<"callJSMethod method:"<<method.c_str()<<endl;
    std::string sReq = method;
    sReq.append("('");
    sReq.append(data.toStdString());
    sReq.append("')");
    CefString lData = sReq;
    m_handler->GetMainFram()->ExecuteJavaScript(lData, L"", 0);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    if(m_handler != NULL)
        ::MoveWindow(m_handler->GetBrowserHostWnd(),
                     0, 0, event->size().width(), event->size().height(), TRUE);

    event->accept();
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    UNREFERENCED_PARAMETER(message);
    MSG* msg = (MSG*)message;
    switch (msg->message) {
    case WM_COPYDATA:
    {
        COPYDATASTRUCT * pcopy = reinterpret_cast<COPYDATASTRUCT*>(msg->lParam);
        std::string sInfo = (char *)pcopy->lpData;
        sInfo = sInfo.substr(0,pcopy->cbData);

        /* excutre command */
        if(msg->wParam == 1000){
            qDebug()<<"excuteCommand:"<<sInfo.c_str()<<endl;
            m_CallMgr.excuteCommand(sInfo);
        }

        /* regeister callback */
        else if(msg->wParam == 1001){
            qDebug()<<"regeister:"<<sInfo.c_str()<<sInfo.length()<<endl;
            QJsonParseError jsonerror;
            QJsonDocument doc = QJsonDocument::fromJson(QString::fromStdString(sInfo).toUtf8(), &jsonerror);

            assert(!doc.isNull());
            assert(jsonerror.error == QJsonParseError::NoError);
            assert(doc.isObject());

            QJsonObject obj = doc.object();
            assert(obj.contains("type")
                   &&obj.contains("method")
                   &&obj.value("type").isDouble()
                   &&obj.value("method").isString());

            std::string method = obj.value("method").toString().toStdString();
            int type = obj.value("type").toInt();

            this->m_CallbackMap[type] = method;
        }

        /* resize browser */
        else if(msg->wParam == 1002){
            QJsonParseError jsonerror;
            QJsonDocument doc = QJsonDocument::fromJson(QString::fromStdString(sInfo).toUtf8(), &jsonerror);

            assert(!doc.isNull());
            assert(jsonerror.error == QJsonParseError::NoError);
            assert(doc.isObject());

            QJsonObject obj = doc.object();
            assert(obj.contains("width")
                   &&obj.contains("height")
                   &&obj.value("width").isDouble()
                   &&obj.value("height").isDouble());

            int width = obj.value("width").toInt();
            int height = obj.value("height").toInt();

            this->setGeometry(this->pos().x(),this->pos().y(),width ,height );
//            this->setMaximumSize(width ,height );
//            this->setMinimumSize(width ,height );
        }

        break;
    }
    default:
        break;
    }
    return QWidget::nativeEvent(eventType, message, result);
}
