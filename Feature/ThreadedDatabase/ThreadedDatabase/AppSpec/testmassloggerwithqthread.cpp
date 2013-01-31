#include "testmassloggerwithqthread.h"

#include "AppSpec/globalobjectregistry.h"
#include "Common/Database/simplelogdatabasemanager.h"

TestMassLoggerWithQThread::TestMassLoggerWithQThread(QObject *parent) :
    QThread(parent)
{
}

void TestMassLoggerWithQThread::run()
{
    this->exec();
}

void TestMassLoggerWithQThread::startWorker(QString id)
{


    this->start();
}

void TestMassLoggerWithQThread::finishedSlot(QString id)
{
    Q_EMIT finishedWithItem(id);
    this->quit();
}
