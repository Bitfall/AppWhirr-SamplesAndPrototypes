#include "mainwindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QThread>
#include <QElapsedTimer>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *mainCentralWidget = new QWidget;
    this->setCentralWidget(mainCentralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainCentralWidget->setLayout(mainLayout);

    _doTestButton = new QPushButton(tr("Start testing"));
    connect(_doTestButton, SIGNAL(clicked()), this, SLOT(_startTesting()));
    mainLayout->addWidget(_doTestButton);

    _testCollection = new ReferenceCountingIdBasedCollection(this);
    _elapsedTimer = new QElapsedTimer;
}

MainWindow::~MainWindow()
{
    delete _elapsedTimer;
}

void MainWindow::_startTesting()
{
    _doTestButton->setEnabled(false);
    _elapsedTimer->start();

    //
    // add test items to the collection
    for(int i = 0; i < 10; ++i)
    {
        _testCollection->addItem(new TestItem(QString::number(i)));
    }

    //
    // add and start testers
    _testerCount = 0;
    for(int i = 0; i < 4; ++i) {
        ++_testerCount;

        bool isRetainMode = ( (i % 2) == 0 );
        DLog("Is retain mode: ") << isRetainMode;
        RefTester *refTester = new RefTester(QString::number(i), _testCollection, isRetainMode);
        QThread *refTesterThread = new QThread;
        connect(refTesterThread, SIGNAL(started()), refTester, SLOT(startTesting()));
        connect(refTester, SIGNAL(finishedWithTesting()), refTesterThread, SLOT(quit()));
        connect(refTester, SIGNAL(finishedWithTesting_Id(QString)), this, SLOT(_testFinished(QString)));
        refTester->moveToThread(refTesterThread);
        refTesterThread->start();
    }
}

void MainWindow::_testFinished(QString testId)
{
    --_testerCount;
    DLog("Test finished (+ remaining): ") << testId << _testerCount;
    if(_testerCount <= 0) {
        DLog("Elapsed time: ") << _elapsedTimer->elapsed();
        DLog("Finished with every test.");
        _doTestButton->setEnabled(true);
    }
}
