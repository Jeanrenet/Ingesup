TEMPLATE = app

QT += qml quick bluetooth
CONFIG += c++11

SOURCES += main.cpp \
    CBLEDiscover.cpp \
    CBLEDeviceInfo.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    CBLEDiscover.h \
    CBLEDeviceInfo.h

DISTFILES +=
