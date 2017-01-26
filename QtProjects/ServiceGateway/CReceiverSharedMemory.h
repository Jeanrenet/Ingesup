#ifndef CRECEIVERSHAREDMEMORY_H
#define CRECEIVERSHAREDMEMORY_H

#include <QTimer>
#include <QSharedMemory>
#include <QDataStream>

class CReceiverSharedMemory : public QObject
{
    Q_OBJECT
public:
    CReceiverSharedMemory();

    double readTemperature() const;

protected slots:
    void eventLoop();

private:
    QTimer  m_timer;
    QSharedMemory   m_sharedMemory;
    double          m_readTemperature;
};

#endif // CRECEIVERSHAREDMEMORY_H
