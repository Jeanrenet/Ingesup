#include "CBLEDeviceInfo.h"

#include <QBluetoothAddress>

CBLEDeviceInfo::CBLEDeviceInfo(const QBluetoothDeviceInfo &deviceInfo)
{
    m_address = deviceInfo.address().toString();
    m_name = deviceInfo.name();
}

QString CBLEDeviceInfo::getAddress()
{
    return m_address;
}
