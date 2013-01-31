#include "mainwindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QThreadPool>
#include <QDir>
#include <QApplication>
#include <QMutex>

#include "AppSpec/testmasslogger.h"
#include "AppSpec/testmassloggerwithqthread_worker.h"
#include "Common/Database/simplelogdatabasemanager.h"
#include "AppSpec/globalobjectregistry.h"
#include "AppSpec/testdatabaseservermanager.h"
#include "AppSpec/test_addtodatabaseserver.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    // do some cleanups
    QDir().remove("testEventBasedDatabase.db");
    QDir().remove("test.db");
    QDir().remove("operation_log.db");

    QWidget *mainCentralWidget = new QWidget();
    this->setCentralWidget(mainCentralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainCentralWidget->setLayout(mainLayout);

    QPushButton *doMagicButton = new QPushButton;
    connect(doMagicButton, SIGNAL(clicked()), this, SLOT(doMagicButtonPressed()));
    doMagicButton->setText(tr("Do magic! (start logging threads)"));
    mainLayout->addWidget(doMagicButton);
}

MainWindow::~MainWindow()
{

}

void MainWindow::doMagicButtonPressed()
{
    // start the server
    disconnect(GlobalObjectRegistry::sharedGlobalObjectRegistry()->getTestDatabaseServerManager(), SIGNAL(serverStarted()), this, SLOT(_serverStartedStartMagic()));
    disconnect(GlobalObjectRegistry::sharedGlobalObjectRegistry()->getTestDatabaseServerManager(), SIGNAL(serverStopped()), this, SLOT(_serverShutDown()));

    connect(GlobalObjectRegistry::sharedGlobalObjectRegistry()->getTestDatabaseServerManager(), SIGNAL(serverStarted()), this, SLOT(_serverStartedStartMagic()));
    connect(GlobalObjectRegistry::sharedGlobalObjectRegistry()->getTestDatabaseServerManager(), SIGNAL(serverStopped()), this, SLOT(_serverShutDown()));

    GlobalObjectRegistry::sharedGlobalObjectRegistry()->getTestDatabaseServerManager()->startServer();

//    DLog("--start--");

//    GlobalObjectRegistry::sharedGlobalObjectRegistry()->getSimpleLogDatabaseManager()->writeToLog("test.db", QString("Test from main thread [thread: %1]").arg((long)QThread::currentThread()));

//    // test with thread-pool
//#if 0
//    for(int i = 0; i < 10; i++) {
//        TestMassLogger *testLogger = new TestMassLogger(QString("-%1-").arg(i));
//        connect(testLogger, SIGNAL(finished(QString)), this, SLOT(threadFinished(QString)));
//        QThreadPool::globalInstance()->start(testLogger);
//    }
//#endif

//    // test with QThread
//#if 1
//    for(int i = 0; i < 10; i++) {
//        DLog("Thread started: ") << i;
////        TestMassLoggerWithQThread *testLoggerWithQThread = new TestMassLoggerWithQThread(QString("-%1-").arg(i));
////        connect(testLoggerWithQThread, SIGNAL(finished(QString)), this, SLOT(threadFinished(QString)));
//////        testLoggerWithQThread->start( ((i%2==0) ? QThread::NormalPriority : QThread::LowPriority) );
////        testLoggerWithQThread->start();

//        QThread *workerThread = new QThread;
//        TestMassLoggerWithQThread_Worker *worker = new TestMassLoggerWithQThread_Worker(QString("-%1-").arg(i));
//        connect(worker, SIGNAL(finishedWithWork(QString)), this, SLOT(threadFinished(QString)));
//        connect(worker, SIGNAL(finishedWithItem(QString)), this, SLOT(itemFinished(QString)));
//        connect(worker, SIGNAL(finished()), workerThread, SLOT(quit()));
//        worker->moveToThread(workerThread);

//        connect(workerThread, SIGNAL(started()), worker, SLOT(doMassLogging()));

//        workerThread->start( ((i%2==0) ? QThread::NormalPriority : QThread::LowPriority) );
////        worker.doMassLogging();
//    }
//#endif
}

void MainWindow::_serverShutDown()
{
    DLog("--server down--");
}

void MainWindow::_serverStartedStartMagic()
{
    DLog("--server started--");
    // send a test message
    GlobalObjectRegistry::sharedGlobalObjectRegistry()->getTestDatabaseServerManager()->addToPeople("test-from-main", 22, "initial test from main thread");

    // test with QThread
    int desiredThreadCnt = 6;
    for(int i = 0; i < desiredThreadCnt; i++) {
        DLog("Thread started: ") << i;

        QThread *workerThread = new QThread;
        QString workId = QString("-%1-").arg(i);
        _testWorkIds.append(workId);
        Test_AddToDatabaseServer *worker = new Test_AddToDatabaseServer(workId);
        connect(worker, SIGNAL(finishedWithWork(QString)), this, SLOT(finishedWithWork(QString)));
        connect(worker, SIGNAL(finishedWithItem(QString)), this, SLOT(itemFinished(QString)));
        connect(worker, SIGNAL(finished()), workerThread, SLOT(quit()));
        worker->moveToThread(workerThread);

        connect(workerThread, SIGNAL(started()), worker, SLOT(doMassLogging()));

        workerThread->start( ((i%2==0) ? QThread::NormalPriority : QThread::LowPriority) );
//        workerThread->start( QThread::NormalPriority );
        //        worker.doMassLogging();
    }
}

void MainWindow::finishedWithWork(QString threadId)
{
    QMutex mutex;
    mutex.lock();

    this->_testWorkIds.removeOne(threadId);

    mutex.unlock();

    if(this->_testWorkIds.isEmpty()) {
        this->finishedWithAddingItems();
    }

//    GlobalObjectRegistry::sharedGlobalObjectRegistry()->getSimpleLogDatabaseManager()->writeToLog("operation_log.db", QString("Test finished: %1").arg(threadId));

//    DLog("--finished: ") << threadId;
}

void MainWindow::finishedWithAddingItems()
{
    connect(GlobalObjectRegistry::sharedGlobalObjectRegistry()->getTestDatabaseServerManager(), SIGNAL(_resultFor_getFromPeopleByAge(QString,int,QString,bool)), this, SLOT(resultFor_getFromPeopleByAge(QString,int,QString,bool)));
//    connect(GlobalObjectRegistry::sharedGlobalObjectRegistry()->getTestDatabaseServerManager(), SIGNAL(_resultFor_getFromPeopleByAge(QString,int,QString,bool)), this, SLOT(resultFor_getFromPeopleByAge(QString,int,QString,bool)));
//    disconnect(GlobalObjectRegistry::sharedGlobalObjectRegistry()->getTestDatabaseServerManager(), SIGNAL(_resultFor_getFromPeopleByAge(QString,int,QString,bool)), this, SLOT(resultFor_getFromPeopleByAge(QString,int,QString,bool)));


    GlobalObjectRegistry::sharedGlobalObjectRegistry()->getTestDatabaseServerManager()->getFromPeopleByAge(4);
    GlobalObjectRegistry::sharedGlobalObjectRegistry()->getTestDatabaseServerManager()->addStopServerToQueue();
//    GlobalObjectRegistry::sharedGlobalObjectRegistry()->getTestDatabaseServerManager()->stopServerImmediatelly();
}

void MainWindow::resultFor_getFromPeopleByAge(QString name,int age,QString notes,bool isSuccess)
{
//    disconnect(GlobalObjectRegistry::sharedGlobalObjectRegistry()->getTestDatabaseServerManager(), SIGNAL(_resultFor_getFromPeopleByAge(QString,int,QString,bool)), this, SLOT(resultFor_getFromPeopleByAge(QString,int,QString,bool)));
    DLog("Result: ") << name << age << notes << isSuccess;
}

void MainWindow::itemFinished(QString item)
{
//    GlobalObjectRegistry::sharedGlobalObjectRegistry()->getSimpleLogDatabaseManager()->writeToLog("operation_log.db", QString("Item finished: %1").arg(item));
}
