QT += core dbus bluetooth
QT -= gui

CONFIG += c++11

TARGET = ServiceGateway
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    CServerBLE.cpp \
    CDbusClient.cpp \
    CReceiverSharedMemory.cpp \
    CStandardServerBLE.cpp

HEADERS += \
    CServerBLE.h \
    CDbusClient.h \
    CReceiverSharedMemory.h \
    CStandardServerBLE.h

target.path = /usr/bin
INSTALLS += target
