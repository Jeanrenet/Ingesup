#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "CBLEDiscover.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    //engine
    QQmlApplicationEngine engine;

    //load class
    CBLEDiscover *bleDiscover = new CBLEDiscover();
    engine.rootContext()->setContextProperty("BLEDiscover", bleDiscover);

    //load QML
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
