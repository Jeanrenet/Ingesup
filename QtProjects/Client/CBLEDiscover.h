#ifndef CBLEDISCOVER_H
#define CBLEDISCOVER_H

#include <QLowEnergyController>
#include <QVariant>
#include <QTimer>

#include "CBLEDeviceInfo.h"

#define CHAR_UUID_ENABLE            0x2aa7
#define UUID_TEMPERATURE            0x2aa6

class CBLEDiscover : public QObject
{
    Q_OBJECT
    Q_PROPERTY(bool enable MEMBER m_enabled NOTIFY enabledChanged)
    Q_PROPERTY(bool connectionState MEMBER m_connected NOTIFY connected)
    Q_PROPERTY(float temperature MEMBER m_temperature NOTIFY temperatureChanged)

public:
    CBLEDiscover();
    ~CBLEDiscover();

protected slots:
    void connectToDevice(const QString &address);
    void connectToService(QLowEnergyService *service);
    void addLowEnergyService(QBluetoothUuid serviceUuid);
    void serviceDetailsDiscovered(QLowEnergyService::ServiceState newState);
    void serviceCharacteristicChanged(const QLowEnergyCharacteristic &c, const QByteArray &value);
    void deviceConnected();

private:
    QList<QObject*>                  m_devices;
    QLowEnergyController            *m_controller;
    QLowEnergyService               *m_connectedService;
    QLowEnergyCharacteristic        m_enabledChar;
    bool                            m_enabled;
    bool                            m_connected;
    float                           m_temperature;

public:
    Q_SIGNAL void enabledChanged();
    Q_SIGNAL void connected();
    Q_SIGNAL void temperatureChanged();

    Q_INVOKABLE void start();
    Q_INVOKABLE void switchEnable(bool value);
};

#endif // CBLEDISCOVER_H
