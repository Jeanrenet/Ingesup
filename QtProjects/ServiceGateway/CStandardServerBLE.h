#ifndef CSTANDARDSERVERBLE_H
#define CSTANDARDSERVERBLE_H

#include "CReceiverSharedMemory.h"
#include <QtBluetooth/qlowenergyadvertisingdata.h>
#include <QtBluetooth/qlowenergyadvertisingparameters.h>
#include <QtBluetooth/qlowenergycharacteristic.h>
#include <QtBluetooth/qlowenergycharacteristicdata.h>
#include <QtBluetooth/qlowenergydescriptordata.h>
#include <QtBluetooth/qlowenergycontroller.h>
#include <QtBluetooth/qlowenergyservice.h>
#include <QtBluetooth/qlowenergyservicedata.h>
#include <QTimer>

class CStandardServerBLE : public QObject
{
    Q_OBJECT
public:
    CStandardServerBLE(CReceiverSharedMemory *receiver);

protected slots:
    void mainLoop();

    void controllerStateChanged(QLowEnergyController::ControllerState state);
private:
    CReceiverSharedMemory       *m_receiver;
    QTimer                      *m_timer;

    QLowEnergyAdvertisingData   m_advertisingData;
    QLowEnergyController        *m_bleController;
    QLowEnergyService           *m_serviceTemperature;
};

#endif // CSTANDARDSERVERBLE_H
