#include "CReceiverSharedMemory.h"

#include <QDebug>

CReceiverSharedMemory::CReceiverSharedMemory()
{
    m_sharedMemory.setKey("SharedMemoryProducer");
    m_sharedMemory.attach(QSharedMemory::ReadOnly);

    connect(&m_timer, SIGNAL(timeout()), this, SLOT(eventLoop()));
    m_timer.start(1000);
}

void CReceiverSharedMemory::eventLoop()
{
    if (m_sharedMemory.isAttached())
    {
        QByteArray data;
        m_sharedMemory.lock();
        data.setRawData((char*)m_sharedMemory.constData(), m_sharedMemory.size());
        QDataStream stream(data);
        stream >> m_readTemperature;

        qDebug() << m_readTemperature << m_sharedMemory.size();

        m_sharedMemory.unlock();
    }
    else
       m_sharedMemory.attach();
}

double CReceiverSharedMemory::readTemperature() const
{
    return m_readTemperature;
}
