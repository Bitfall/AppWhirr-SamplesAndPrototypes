#ifndef TESTDATABASESERVER_H
#define TESTDATABASESERVER_H

#include "Common/Database/basedatabase.h"

#include <QSqlQuery>
#include <QVariant>
#include <QSqlError>

class DatabaseWorkAgentBase : public QObject {
    Q_OBJECT
public:
    explicit DatabaseWorkAgentBase(QObject *parent = 0) : QObject(parent) {}

    virtual bool doYourWork(QSqlDatabase databaseToWorkOn) = 0;

    virtual QString getAgentTypeId() const = 0;

protected:
    void logQueryExecutionFailedWithLastErrorForQuery(QSqlQuery query)
    {
        WLog("Query execution failed with error: ") << query.lastError().text() << " [for query: " << query.lastQuery() << "]";
    }
};

class AddToPeopleDatabaseWorkAgent : public DatabaseWorkAgentBase {
    Q_OBJECT
public:
    explicit AddToPeopleDatabaseWorkAgent(QString name, int age, QString notes, QObject *parent = 0) : DatabaseWorkAgentBase(parent), _name(name), _age(age), _notes(notes) {}

    bool doYourWork(QSqlDatabase databaseToWorkOn) {
        static QString queryString("INSERT INTO people (name, age, notes) VALUES (?, ?, ?)");
        QSqlQuery query(databaseToWorkOn);
        query.prepare(queryString);
        query.bindValue(0, _name);
        query.bindValue(1, QVariant(_age));
        query.bindValue(2, _notes);
        if(!query.exec()) {
            this->logQueryExecutionFailedWithLastErrorForQuery(query);
            return false;
        }
        return true;
    }

    QString getAgentTypeId() const { return "AddToPeopleDatabaseWorkAgent"; }

private:
    QString _name;
    int _age;
    QString _notes;
};

class GetFromPeopleByAgeDatabaseWorkAgent : public DatabaseWorkAgentBase {
    Q_OBJECT
public:
    explicit GetFromPeopleByAgeDatabaseWorkAgent(int age, QObject *parent = 0) : DatabaseWorkAgentBase(parent), _age(age) {}

    bool doYourWork(QSqlDatabase databaseToWorkOn) {
        static QString queryString("SELECT name, age, notes FROM people WHERE age=? LIMIT 1");
        QSqlQuery query(databaseToWorkOn);
        query.prepare(queryString);
        query.bindValue(0, QVariant(_age));
        if(!query.exec()) {
            this->logQueryExecutionFailedWithLastErrorForQuery(query);
            return false;
        }
        else if(query.next()){
            this->_name = query.value(0).toString();
            this->_age = query.value(1).toInt();
            this->_notes = query.value(2).toString();
        }
        return true;
    }

    QString getFoundName() { return _name; }
    int getFoundAge() { return _age; }
    QString getFoundNotes() { return _notes; }

    QString getAgentTypeId() const { return "GetFromPeopleByAgeDatabaseWorkAgent"; }

private:
    QString _name;
    int _age;
    QString _notes;
};

class TestDatabaseWorker : public BaseDatabase
{
    Q_OBJECT
public:
    TestDatabaseWorker(QObject *parent = 0);

Q_SIGNALS: // server - worker communication signals
    void finishedWithWork(DatabaseWorkAgentBase *workAgent, bool isSuccess);
    void initialized();
    void shutDownHappened();

public Q_SLOTS:
    void performThisWork(DatabaseWorkAgentBase *workAgent);
    void openAndInitialize();
    void closeAndShutDown();

protected:
    QString getDatabasePath();
    bool copyDatabaseFromResourceToPath(QString path) { return false; }
    bool fillDatabaseWithBasicData(QSqlDatabase databaseToFill);

private:
    QSqlDatabase _db;
};

#endif // TESTDATABASESERVER_H
