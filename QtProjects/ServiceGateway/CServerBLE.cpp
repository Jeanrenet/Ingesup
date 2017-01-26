#include "CServerBLE.h"

#define SERVICE_UUID                0x1820
#define CHAR_UUID_TEMPERATURE       0x2aa6
#define CHAR_UUID_ENABLE            0x2aa7

CServerBLE::CServerBLE(CDbusClient *dbusclient, CReceiverSharedMemory *receiver) : m_receiver(receiver), m_dbusclient(dbusclient)
{
    m_timerTemperature = new QTimer;
    connect(m_timerTemperature, SIGNAL(timeout()), this, SLOT(updateTemperature()));

    initServer();
}

CServerBLE::~CServerBLE()
{
    delete m_timerTemperature;
}

void CServerBLE::initServer()
{
    QBluetoothUuid serviceuuid((quint32)SERVICE_UUID);
    QBluetoothUuid temperatureUuid((quint32)CHAR_UUID_TEMPERATURE);
    QBluetoothUuid enableuuid((quint32)CHAR_UUID_ENABLE);

                                            //serveur
    m_advertisingData.setDiscoverability(QLowEnergyAdvertisingData::DiscoverabilityGeneral);  //Mode d'accessibilité
    //m_advertisingData.setLocalName("");                                    //Nom du serveur
    m_advertisingData.setServices(QList<QBluetoothUuid>() <<
                                serviceuuid
                                );                         //Ajout des services prédéfinis

    //Création de la charactéristique
    QLowEnergyCharacteristicData charEnable = createCharacteristic(enableuuid,
                                                                   QLowEnergyCharacteristic::Write | QLowEnergyCharacteristic::Read);
    QLowEnergyCharacteristicData charTemperature = createCharacteristic(temperatureUuid,
                                                                   QLowEnergyCharacteristic::Notify);

    //Couplage du service avec la caractéristique créée.
    QLowEnergyServiceData serviceData;
    serviceData.setType(QLowEnergyServiceData::ServiceTypePrimary);
    serviceData.setUuid(serviceuuid);
    serviceData.addCharacteristic(charEnable);
    serviceData.addCharacteristic(charTemperature);

    //création du controlleur BLE
    m_bleController = QLowEnergyController::createPeripheral();
    connect(m_bleController,
            SIGNAL(stateChanged(QLowEnergyController::ControllerState)),
            this,
            SLOT(controllerStateChanged(QLowEnergyController::ControllerState)));

    //ajout du service
    m_serviceRelay = m_bleController->addService(serviceData);

    //permettra de récupérer les données reçues
    connect(m_serviceRelay,
            SIGNAL(characteristicChanged(QLowEnergyCharacteristic,QByteArray)),
            this,
            SLOT(characteristicChanged(QLowEnergyCharacteristic,QByteArray)));

    //démarrage "advertising"
    m_bleController->startAdvertising(QLowEnergyAdvertisingParameters(), m_advertisingData, m_advertisingData);
}

void CServerBLE::controllerStateChanged(QLowEnergyController::ControllerState state)
{
    if (state == QLowEnergyController::UnconnectedState)
    {
        qDebug() << "Client Disconnected";
        m_bleController->startAdvertising(QLowEnergyAdvertisingParameters(), m_advertisingData, m_advertisingData);

        m_timerTemperature->stop();
    }

    if (state == QLowEnergyController::ConnectedState)
    {
        qDebug() << "Client Connected";

        //démarrage lecture température
        m_timerTemperature->start(500);
    }
}

void CServerBLE::characteristicChanged(QLowEnergyCharacteristic c, QByteArray data)
{
    switch(c.uuid().toUInt32())
    {
    case CHAR_UUID_ENABLE:
        m_dbusclient->enableTempRead(data.toInt());
        break;
    }
}

void CServerBLE::updateTemperature()
{
    // récupération de la caratéristique du service
    QLowEnergyCharacteristic characteristic = m_serviceRelay->characteristic(QBluetoothUuid((quint32)CHAR_UUID_TEMPERATURE));
    Q_ASSERT(characteristic.isValid());

    //mise à jour de la donnée
    m_serviceRelay->writeCharacteristic(characteristic, QByteArray::number(m_receiver->readTemperature())); // Potentially causes notification.
}

void CServerBLE::setValue(QBluetoothUuid uuid, quint32 value)
{
    QLowEnergyCharacteristic characteristic = m_serviceRelay->characteristic(uuid);
    Q_ASSERT(characteristic.isValid());
    m_serviceRelay->writeCharacteristic(characteristic, QByteArray::number(value)); // Potentially causes notification.
}

QLowEnergyCharacteristicData CServerBLE::createCharacteristic(QBluetoothUuid uuid, QLowEnergyCharacteristic::PropertyTypes type)
{
    QLowEnergyCharacteristicData charData;
    charData.setUuid(QBluetoothUuid(uuid)); //uuid définie de la charactéristique
    charData.setValue(QByteArray(2, 0));
    charData.setProperties(type); //précise le type de la propriété
    const QLowEnergyDescriptorData clientConfig(QBluetoothUuid::ClientCharacteristicConfiguration, QByteArray(2, 0));
    charData.addDescriptor(clientConfig);

    return charData;
}
