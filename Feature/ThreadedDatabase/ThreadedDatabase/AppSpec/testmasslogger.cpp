#include "testmasslogger.h"

#include <QThread>

#include "Common/Database/simplelogdatabasemanager.h"
#include "AppSpec/globalobjectregistry.h"

TestMassLogger::TestMassLogger(QString testId) :
    QObject(0),
    _testId(testId)
{
}

void TestMassLogger::run()
{
    for(int i = 0; i < 10; i++) {
        GlobalObjectRegistry::sharedGlobalObjectRegistry()->getSimpleLogDatabaseManager()->writeToLog("test.db", QString("Test (id:%1) %2 [from thread: %3]").arg(this->_testId).arg(i).arg((long)QThread::currentThread()));

        Q_EMIT finishedWithItem(QString("%1").arg(i));
    }

    Q_EMIT finished(this->_testId);
}
