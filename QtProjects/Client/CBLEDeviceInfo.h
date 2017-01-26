#ifndef CBLEDEVICEINFO_H
#define CBLEDEVICEINFO_H

#include <QObject>
#include <QBluetoothDeviceInfo>

class CBLEDeviceInfo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString deviceAddress MEMBER m_address)
    Q_PROPERTY(QString deviceName MEMBER m_name)

public:
    CBLEDeviceInfo(const QBluetoothDeviceInfo &deviceInfo);
    QString getAddress();

private:
    QString m_address;
    QString m_name;
};

#endif // CBLEDEVICEINFO_H
