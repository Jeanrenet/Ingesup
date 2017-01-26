#include "CProducer.h"

#include <QDBusConnection>
#include <QDebug>

#define SERVICE_NAME "service.com.service"

#define BOARD_TEMP "/sys/devices/virtual/thermal/thermal_zone0/temp"

CProducer::CProducer() : m_enabled(true)
{
    /**
      * SHAREDMEMORY INIT
      **/
    setKey("SharedMemoryProducer");

    if (this->attach())
        this->detach();
    create(sizeof(double), QSharedMemory::ReadWrite);

    /**
      * QFILE INIT
      **/
    m_readTemperatureFile = new QFile(BOARD_TEMP);

    /**
      * QTIMER INIT
      */
    m_eventLoopTimer =  new QTimer();

    connect(m_eventLoopTimer,
            SIGNAL(timeout()),
            this,
            SLOT(eventLoop()));

    m_eventLoopTimer->start(1000);//msec

    /**
      * DBUS INIT
      **/
    if (!QDBusConnection::systemBus().isConnected())
    {
        qDebug() << "DBUS not started !";
    }
    if (!QDBusConnection::systemBus().registerService(SERVICE_NAME))
    {
        qDebug() << " Already Registered !";
    }

    QDBusConnection::systemBus().registerObject("/",
                                                this,
                                                QDBusConnection::ExportAllInvokables);
}

CProducer::~CProducer()
{
    m_readTemperatureFile->close();
    delete m_readTemperatureFile;

    m_eventLoopTimer->stop();
    delete m_eventLoopTimer;
}

void CProducer::enableTempRead(bool value)
{
    m_enabled = value;
}

bool CProducer::tempReadIsEnabled()
{
    return m_enabled;
}

void CProducer::eventLoop()
{
    if (!m_enabled)
        return;

    bool ret = m_readTemperatureFile->open(QIODevice::ReadOnly);
    if (ret) //sucessful
    {
        //read value
        QByteArray array = m_readTemperatureFile->readAll();
        array.remove(array.length() - 1, 1); //remove last character

        m_boardTemperature = array.toDouble() / 1000.0;
        qDebug() << m_boardTemperature;
        m_readTemperatureFile->close();

        //write to shared
        if (this->isAttached())
            {
                QByteArray sharedData;
                QDataStream stream(&sharedData, QIODevice::WriteOnly);
                stream << m_boardTemperature;

                this->lock();
                char *to = (char*)this->data();
                memcpy(to, sharedData.data(), qMin(this->size(), (qint32)sharedData.size()));
                this->unlock();
            }
            else
                this->attach();
    }
}

double CProducer::boardTemperature() const
{
    return m_boardTemperature;
}
