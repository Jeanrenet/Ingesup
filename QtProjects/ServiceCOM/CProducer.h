#ifndef CPRODUCERFULL_H
#define CPRODUCERFULL_H

#include <QFile>
#include <QTimer>
#include <QDebug>
#include <QSharedMemory>
#include <QDataStream>

class CProducer : public QSharedMemory
{
    Q_OBJECT
public:
    CProducer();
    ~CProducer();

public:
    Q_INVOKABLE void enableTempRead(bool value);
    Q_INVOKABLE bool tempReadIsEnabled();

public:
    double boardTemperature() const;

protected slots:
    void eventLoop();

private:
    QFile   *m_readTemperatureFile;
    QTimer  *m_eventLoopTimer;
    double  m_boardTemperature;
    bool    m_enabled;
};

#endif // CPRODUCERFULL_H
