#-------------------------------------------------
#
# Project created by QtCreator 2018-11-06T11:34:00
#
#-------------------------------------------------

QT       += core gui network webengine webenginewidgets
CONFIG   += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = native-client
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    aboutdialog.cpp \
    namedialog.cpp \
    configdialog.cpp \
    webeditordialog.cpp \
    webviewerdialog.cpp

HEADERS  += mainwindow.h \
    aboutdialog.h \
    namedialog.h \
    configdialog.h \
    webeditordialog.h \
    webviewerdialog.h

FORMS    += mainwindow.ui \
    aboutdialog.ui \
    namedialog.ui \
    configdialog.ui \
    webeditordialog.ui \
    webviewerdialog.ui

RESOURCES += \
    resources.qrc
