#include "simplelogdatabasemanager.h"

#include <QDateTime>

#include <QMutex>

// sql
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

// -------------------------
// --- SimpleLogDatabase ---

SimpleLogDatabaseManager::SimpleLogDatabase::SimpleLogDatabase(QString logFilePath, QString baseConnectionName) :
    BaseDatabase(baseConnectionName, NULL),
    _logFilePath(logFilePath)
{}

QString SimpleLogDatabaseManager::SimpleLogDatabase::getDatabasePath() {
    return this->_logFilePath;
}

bool SimpleLogDatabaseManager::SimpleLogDatabase::fillDatabaseWithBasicData(QSqlDatabase databaseToFill)
{
    static QString queryString("CREATE TABLE logs (logText TEXT, timestampText TEXT, timestamp NUMERIC)");
    QSqlQuery query(databaseToFill);
    query.prepare(queryString);
    if(!query.exec()) {
        this->logQueryExecutionFailedWithLastErrorForQuery(query);
        return false;
    }

    return true;
}

void SimpleLogDatabaseManager::SimpleLogDatabase::writeToLog(QString logText)
{
    {
        QSqlDatabase db = this->openDatabaseConnectionAndReturnDatabase();

        static QString queryString("INSERT INTO logs (logText, timestampText, timestamp) VALUES (?, ?, ?)");
        QSqlQuery query(db);
        query.prepare(queryString);
        query.bindValue(0, logText);
        query.bindValue(1, QDateTime::currentDateTime().toString("dd.MM.yyyy : hh:mm:ss"));
        query.bindValue(2, QDateTime::currentMSecsSinceEpoch());
        if(!query.exec()) {
            this->logQueryExecutionFailedWithLastErrorForQuery(query);
        }
        query.clear();
        db.close();
    }

    this->closeDatabaseConnection();
}

// --------------------------------
// --- SimpleLogDatabaseManager ---

void SimpleLogDatabaseManager::writeToLog(QString logFilePath, QString logText)
{
    QMutex mutex;
    mutex.lock();

    DLog(logText);

    SimpleLogDatabaseManager::SimpleLogDatabase *logDatabase = new SimpleLogDatabaseManager::SimpleLogDatabase(logFilePath, logFilePath);
    logDatabase->writeToLog(logText);
    delete logDatabase;

    mutex.unlock();
}
