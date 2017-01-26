#include <QCoreApplication>

#include "CProducer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() << "Hello IngeSup !";

    //First example
    //new CProducer();

    //Example With Share
    //new CProducerWithSharedMemory();

    //Full Example
    new CProducer();

    return a.exec();
}
