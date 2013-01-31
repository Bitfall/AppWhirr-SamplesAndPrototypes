#ifndef TEST_ADDTODATABASESERVER_H
#define TEST_ADDTODATABASESERVER_H

#include <QObject>

#include <QThread>

#include "globalobjectregistry.h"
#include "testdatabaseservermanager.h"

class Test_AddToDatabaseServer : public QObject
{
    Q_OBJECT
public:
    explicit Test_AddToDatabaseServer(QString id, QObject *parent = 0) : QObject(parent), _id(id) {}

public Q_SLOTS:
    void doMassLogging()
    {
        for(int i = 0; i < 10; i++) {
//            DLog("Task: ") << i;
            GlobalObjectRegistry::sharedGlobalObjectRegistry()->getTestDatabaseServerManager()->addToPeople(QString("Name %1").arg(i), i, QString("Test (id:%1) %2 [from thread: %3]").arg(this->_id).arg(i).arg((long)QThread::currentThread()));

            Q_EMIT finishedWithItem(QString("%1").arg(i));
        }

        Q_EMIT finishedWithWork(this->_id);
        Q_EMIT finished();
    }

Q_SIGNALS:
    void finishedWithItem(QString item);
    void finishedWithWork(QString id);
    void finished();

private:
     QString _id;
};

#endif // TEST_ADDTODATABASESERVER_H
