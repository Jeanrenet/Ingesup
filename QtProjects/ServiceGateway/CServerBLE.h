#ifndef CSERVERBLE_H
#define CSERVERBLE_H

#include <QtBluetooth/qlowenergyadvertisingdata.h>
#include <QtBluetooth/qlowenergyadvertisingparameters.h>
#include <QtBluetooth/qlowenergycharacteristic.h>
#include <QtBluetooth/qlowenergycharacteristicdata.h>
#include <QtBluetooth/qlowenergydescriptordata.h>
#include <QtBluetooth/qlowenergycontroller.h>
#include <QtBluetooth/qlowenergyservice.h>
#include <QtBluetooth/qlowenergyservicedata.h>
#include <QtEndian>
#include <QFile>
#include <QTimer>
#include "CReceiverSharedMemory.h"
#include "CDbusClient.h"

class CServerBLE : public QObject
{
    Q_OBJECT
public:
    CServerBLE(CDbusClient *dbusclient, CReceiverSharedMemory *receiver);
    ~CServerBLE();

public:
    void initServer();

protected slots:
    void controllerStateChanged(QLowEnergyController::ControllerState state);
    void characteristicChanged(QLowEnergyCharacteristic c, QByteArray data);
    void updateTemperature();

protected:
    QLowEnergyCharacteristicData createCharacteristic(QBluetoothUuid uuid,  QLowEnergyCharacteristic::PropertyTypes type);
    void setValue(QBluetoothUuid uuid, quint32 value);

private:
    QLowEnergyAdvertisingData   m_advertisingData;
    QLowEnergyService           *m_serviceRelay;
    QLowEnergyController        *m_bleController;
    QTimer                      *m_timerTemperature;

    CReceiverSharedMemory       *m_receiver;
    CDbusClient                 *m_dbusclient;
};

#endif // CSERVERBLE_H
