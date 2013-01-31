#ifndef TESTDATABASESERVERMANAGER_H
#define TESTDATABASESERVERMANAGER_H

#include <QObject>

class TestDatabaseWorker;
class DatabaseWorkAgentBase;

class TestDatabaseServerManager : public QObject
{
    Q_OBJECT
public:
    explicit TestDatabaseServerManager(QObject *parent = 0);

    void startServer();
    void addStopServerToQueue();
    void stopServerImmediatelly();

    void addToPeople(QString name, int age, QString notes);
    void getFromPeopleByAge(int age);

Q_SIGNALS: // public signals
    void serverStarted();
    void serverStopped();

    // main callbacks
    void _resultFor_getFromPeopleByAge(QString name, int age, QString notes, bool isSuccess);

Q_SIGNALS: // server-worker communication signals
    void _addShutDownToWorkerQueue();
    void _addInitializeToWorkerQueue();
    void _addThisWorkToWorkerQueue(DatabaseWorkAgentBase *workAgent);

private Q_SLOTS:
    // thread
    void _serverThreadStarted();
    void _serverThreadFinished();
    // worker
    void _workerInitialized();
    void _workerShutDownHappened();
    void _finishedWithWork(DatabaseWorkAgentBase *workAgent, bool isSuccess);

private:
//    TestDatabaseWorker *_worker;
    bool _isStarted;
    QThread *_serverThread;
};

#endif // TESTDATABASESERVERMANAGER_H
