#include "testmassloggerwithqthread_worker.h"

#include <QThread>

#include "AppSpec/globalobjectregistry.h"
#include "Common/Database/simplelogdatabasemanager.h"

TestMassLoggerWithQThread_Worker::TestMassLoggerWithQThread_Worker(QString id, QObject *parent) :
    QObject(parent),
    _id(id)
{
}

void TestMassLoggerWithQThread_Worker::doMassLogging()
{
    for(int i = 0; i < 10; i++) {
        DLog("Task: ") << i;
        GlobalObjectRegistry::sharedGlobalObjectRegistry()->getSimpleLogDatabaseManager()->writeToLog("test.db", QString("Test (id:%1) %2 [from thread: %3]").arg(this->_id).arg(i).arg((long)QThread::currentThread()));

        Q_EMIT finishedWithItem(QString("%1").arg(i));
    }

    Q_EMIT finishedWithWork(this->_id);
    Q_EMIT finished();
}
