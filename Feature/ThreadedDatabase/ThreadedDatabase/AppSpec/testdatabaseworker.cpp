#include "testdatabaseworker.h"

#include <QVariant>
#include <QSqlQuery>

TestDatabaseWorker::TestDatabaseWorker(QObject *parent) :
    BaseDatabase("database-worker", parent)
{
}

QString TestDatabaseWorker::getDatabasePath() {
    return "testEventBasedDatabase.db";
}

bool TestDatabaseWorker::fillDatabaseWithBasicData(QSqlDatabase databaseToFill)
{
    static QString queryString("CREATE TABLE people (id INTEGER PRIMARY KEY, name TEXT, age NUMERIC, notes TEXT)");
    QSqlQuery query(databaseToFill);
    query.prepare(queryString);
    if(!query.exec()) {
        this->logQueryExecutionFailedWithLastErrorForQuery(query);
        return false;
    }

    return true;
}

void TestDatabaseWorker::openAndInitialize() {
    this->_db = this->openDatabaseConnectionAndReturnDatabase();
    Q_EMIT initialized();
}

void TestDatabaseWorker::closeAndShutDown() {
    DLog("--close--");
    this->_db.close();
    this->closeDatabaseConnection();

    Q_EMIT shutDownHappened();
}

void TestDatabaseWorker::performThisWork(DatabaseWorkAgentBase *workAgent)
{
    bool isSuccess = workAgent->doYourWork(this->_db);
    if(!isSuccess) {
//        this->logQueryExecutionFailedWithLastErrorForQuery();
        DLog("Worker failed.");
    }
    else {
        DLog("Worker Success.");
    }
    Q_EMIT finishedWithWork(workAgent, isSuccess    );
}
