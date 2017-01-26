QT += core dbus
QT -= gui

CONFIG += c++11

TARGET = ServiceCOM
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    CProducer.cpp \

HEADERS += \
    CProducer.h \    

target.path = /usr/bin
INSTALLS += target
