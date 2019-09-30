#-------------------------------------------------
#
# Project created by QtCreator 2019-09-20T17:31:36
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CallerApp
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# 根据目标系统加载文件
#DEFINES += xp
DEFINES += x64
if(contains(DEFINES,xp)){

INCLUDEPATH += CEF/include2623

LIBS += -L$${PWD}/lib/chrome2623/x32/Release -llibcef -llibcef_dll_wrapper
}
else{

INCLUDEPATH += CEF/include3683

if(contains(DEFINES,x64)){
LIBS += -L$${PWD}/lib/chrome3683/x64/Release -llibcef -llibcef_dll_wrapper
}
else{
LIBS += -L$${PWD}/lib/chrome3683/x32/Release -llibcef -llibcef_dll_wrapper
}
}

SOURCES += \
        main.cpp \
    CEF/CefHandler.cpp \
    CEF/MyCefApp.cpp \
    CEF/V8handler.cpp \
    mainwindow.cpp \
    minidumphandler.cpp \
    logger.cpp \
    callingmanager.cpp \
    ConfigOperator.cpp

HEADERS += \
    CEF/CefHandler.h \
    CEF/MyCefApp.h \
    CEF/util.h \
    CEF/V8handler.h \
    mainwindow.h \
    minidumphandler.h \
    logger.h \
    callingmanager.h \
    ConfigOperator.h

FORMS += \
    mainwindow.ui

RESOURCES += \
    resource.qrc

RC_FILE  += version.rc \
