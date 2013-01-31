#include "testdatabaseservermanager.h"

#include <QThread>
#include <QMutex>
#include <QApplication>

#include "testdatabaseworker.h"

TestDatabaseServerManager::TestDatabaseServerManager(QObject *parent) :
    QObject(parent),
    _isStarted(false),
    _serverThread(0)
{

}

void TestDatabaseServerManager::startServer()
{
    QMutex mutex;
    mutex.lock();

    if(this->_isStarted) {
        mutex.unlock();
        return;
    }

    TestDatabaseWorker *worker = new TestDatabaseWorker;

    // worker - server communication connections
    connect(this, SIGNAL(_addInitializeToWorkerQueue()), worker, SLOT(openAndInitialize()));
    connect(this, SIGNAL(_addShutDownToWorkerQueue()), worker, SLOT(closeAndShutDown()));
    connect(this, SIGNAL(_addThisWorkToWorkerQueue(DatabaseWorkAgentBase*)), worker, SLOT(performThisWork(DatabaseWorkAgentBase*)));

    connect(worker, SIGNAL(initialized()), this, SLOT(_workerInitialized()));
    connect(worker, SIGNAL(shutDownHappened()), this, SLOT(_workerShutDownHappened()));
    connect(worker, SIGNAL(finishedWithWork(DatabaseWorkAgentBase*,bool)), this, SLOT(_finishedWithWork(DatabaseWorkAgentBase*,bool)));

    // server thread creation and connections
//    if(_serverThread == NULL) {
        _serverThread = new QThread;
        connect(_serverThread, SIGNAL(started()), this, SLOT(_serverThreadStarted()));
        connect(_serverThread, SIGNAL(finished()), this, SLOT(_serverThreadFinished()));
//    }

    worker->moveToThread(_serverThread);
    _serverThread->start();
    DLog("--server thread initialized--");

    this->_isStarted = true;
    mutex.unlock();
}

void TestDatabaseServerManager::addStopServerToQueue()
{
    DLog("--stop server requested--");
    Q_EMIT _addShutDownToWorkerQueue();
}

void TestDatabaseServerManager::stopServerImmediatelly()
{
    QMutex mutex;
    mutex.lock();

    if(!this->_isStarted) {
        mutex.unlock();
        return;
    }

    DLog("Worker is not stopped correctly");
    this->_serverThread->quit();

    this->_isStarted = false;
    mutex.unlock();
}

void TestDatabaseServerManager::_serverThreadStarted()
{
    DLog("--server thread started---");
    // start to initialize the worker
    Q_EMIT _addInitializeToWorkerQueue();
}

void TestDatabaseServerManager::_serverThreadFinished()
{
    DLog("--server thread finished---");
}

void TestDatabaseServerManager::_workerInitialized()
{
    DLog("--worker initialized---");
    // worker initialized - server is ready
    Q_EMIT serverStarted();
}

void TestDatabaseServerManager::_workerShutDownHappened()
{
    DLog("--worker shutdown---");

    QMutex mutex;
    mutex.lock();

    if(!this->_isStarted) {
        mutex.unlock();
        return;
    }

    this->_serverThread->quit();

    this->_isStarted = false;
    mutex.unlock();
}

void TestDatabaseServerManager::addToPeople(QString name, int age, QString notes)
{
//    DLog("Add to people");
    Q_EMIT _addThisWorkToWorkerQueue(new AddToPeopleDatabaseWorkAgent(name, age, notes));
}

void TestDatabaseServerManager::getFromPeopleByAge(int age) {
    Q_EMIT _addThisWorkToWorkerQueue(new GetFromPeopleByAgeDatabaseWorkAgent(age));
}

void TestDatabaseServerManager::_finishedWithWork(DatabaseWorkAgentBase *workAgent, bool isSuccess)
{
    DLog("Finished work");

    if(workAgent->getAgentTypeId() == "GetFromPeopleByAgeDatabaseWorkAgent") {
        GetFromPeopleByAgeDatabaseWorkAgent *castedAgent = dynamic_cast<GetFromPeopleByAgeDatabaseWorkAgent *>(workAgent);
        if(castedAgent != NULL) {
            Q_EMIT _resultFor_getFromPeopleByAge(castedAgent->getFoundName(), castedAgent->getFoundAge(), castedAgent->getFoundNotes(), isSuccess);
        } else {
            WLog("Cannot cast the worker. Error.");
        }
    }

    delete workAgent;
}
