#include <QCoreApplication>

#include "CReceiverSharedMemory.h"
#include "CDbusClient.h"
#include "CStandardServerBLE.h"
#include "CServerBLE.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    //shared
    CReceiverSharedMemory *readData = new CReceiverSharedMemory;

    //dbus
    CDbusClient *dbusclient = new CDbusClient;

    //test dbus
    dbusclient->enableTempRead(false);

    //ble standard
    //CStandardServerBLE * standardBLE = new CStandardServerBLE(readData);

    //ble custom
    //CServerBLE   *serverBLE = new CServerBLE(dbusclient, readData);
    return a.exec();
}
