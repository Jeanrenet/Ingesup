#include "CStandardServerBLE.h"

uint32_t float754tofloat11073(float value)
{
    uint8_t  exponent = 0xFE; //exponent is -2
    uint32_t mantissa = (uint32_t)(value * 100);

    return (((uint32_t)exponent) << 24) | mantissa;
}

CStandardServerBLE::CStandardServerBLE(CReceiverSharedMemory *receiver)
{
    m_receiver = receiver;


    m_timer = new QTimer();
    connect(m_timer, SIGNAL(timeout()), this, SLOT(mainLoop()));

    //init
    QLowEnergyAdvertisingData m_advertisingData;                                              //serveur
    m_advertisingData.setDiscoverability(QLowEnergyAdvertisingData::DiscoverabilityGeneral);  //Mode d'accessibilité
    m_advertisingData.setServices(QList<QBluetoothUuid>() <<
                                  QBluetoothUuid::HealthThermometer
                                  ); //Ajout des services prédéfinis

    //Création de la charactéristique
    QLowEnergyCharacteristicData charTemperature;
    //spécification de la caractéristique voulue
    charTemperature.setUuid(QBluetoothUuid::TemperatureMeasurement);
    charTemperature.setValue(QByteArray(2, 0));
    //spécifique à la documentation bluetooth
    charTemperature.setProperties(QLowEnergyCharacteristic::Indicate);
    //Ajout d'un descripteur
    const QLowEnergyDescriptorData clientConfigTemp(QBluetoothUuid::ClientCharacteristicConfiguration,  QByteArray(2, 0));
    charTemperature.addDescriptor(clientConfigTemp);
    //Couplage du service avec la caractéristique créée.
    QLowEnergyServiceData serviceTemperatureData;
    serviceTemperatureData.setType(QLowEnergyServiceData::ServiceTypePrimary);
    serviceTemperatureData.setUuid(QBluetoothUuid::HealthThermometer);
    serviceTemperatureData.addCharacteristic(charTemperature);

    //advertise
    m_bleController = QLowEnergyController::createPeripheral();
    m_serviceTemperature = m_bleController->addService(serviceTemperatureData);
    m_bleController->startAdvertising(QLowEnergyAdvertisingParameters(), m_advertisingData, m_advertisingData);

    m_timer->start(500);

    connect(m_bleController,
            SIGNAL(stateChanged(QLowEnergyController::ControllerState)),
            this,
            SLOT(controllerStateChanged(QLowEnergyController::ControllerState)));
}

void CStandardServerBLE::mainLoop()
{
    quint32 dataToSend = float754tofloat11073(m_receiver->readTemperature());

    //Création de la donnée
    QByteArray value;
    value.append(char(0)); // Flags spécifiant le format de la valeur

    //Stockage du quint32 dans un QByteArray
    value.append(reinterpret_cast<const char*>(&dataToSend), sizeof(dataToSend)); // Valeur à envoyer

    // récupération de la caratéristique du service
    QLowEnergyCharacteristic characteristic = m_serviceTemperature->characteristic(QBluetoothUuid::TemperatureMeasurement);
    Q_ASSERT(characteristic.isValid());

    //mise à jour de la donnée
    m_serviceTemperature->writeCharacteristic(characteristic, value); // Potentially causes notification.
}

void CStandardServerBLE::controllerStateChanged(QLowEnergyController::ControllerState state)
{
    if (state == QLowEnergyController::UnconnectedState)
        m_bleController->startAdvertising(QLowEnergyAdvertisingParameters(), m_advertisingData, m_advertisingData);
}
