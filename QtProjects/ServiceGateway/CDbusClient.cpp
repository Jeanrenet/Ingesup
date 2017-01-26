#include "CDbusClient.h"

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QDebug>

#define SERVICE_NAME "service.com.service"

CDbusClient::CDbusClient()
{
    if (!QDBusConnection::systemBus().isConnected())
    {
        qDebug() << "DBUS not started !";
    }
}

void CDbusClient::enableTempRead(bool value)
{
    QDBusInterface iface(SERVICE_NAME, "/", "", QDBusConnection::systemBus());
    if (iface.isValid())
    {
        iface.call("enableTempRead", value);
    }
}

bool CDbusClient::tempReadIsEnabled()
{
    QDBusInterface iface(SERVICE_NAME, "/", "", QDBusConnection::systemBus());
    if (iface.isValid())
    {
        QDBusReply<bool> reply = iface.call("tempReadIsEnabled");
        if (reply.isValid())
        {
            return reply.value();
        }
    }
    return false;
}
