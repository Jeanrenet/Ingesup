#ifndef CDBUSCLIENT_H
#define CDBUSCLIENT_H

class CDbusClient
{
public:
    CDbusClient();

public:
    void enableTempRead(bool value);
    bool tempReadIsEnabled();
};

#endif // CDBUSCLIENT_H
