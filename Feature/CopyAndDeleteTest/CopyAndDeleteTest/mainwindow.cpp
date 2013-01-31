#include "mainwindow.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>

#include "Common/Helpers/pathhelper.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *mainCentralWidget = new QWidget;
    this->setCentralWidget(mainCentralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainCentralWidget->setLayout(mainLayout);

    _testSrcDirLineEdit = new QLineEdit;
    _testSrcDirLineEdit->setPlaceholderText(tr("Test SOURCE dir path"));
    mainLayout->addWidget(_testSrcDirLineEdit);

    _testDestDirLineEdit = new QLineEdit;
    _testDestDirLineEdit->setPlaceholderText(tr("Test COPY TARGET dir path"));
    mainLayout->addWidget(_testDestDirLineEdit);

    QPushButton *startCopyTestingButton = new QPushButton(tr("Start copy test"));
    connect(startCopyTestingButton, SIGNAL(clicked()), this, SLOT(_startCopyTest()));
    mainLayout->addWidget(startCopyTestingButton);

    QPushButton *startDeleteTestingButton = new QPushButton(tr("Start delete test"));
    connect(startDeleteTestingButton, SIGNAL(clicked()), this, SLOT(_startDeleteTest()));
    mainLayout->addWidget(startDeleteTestingButton);

    this->resize(500, 200);
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::_startCopyTest()
{
    DLog("-- start COPY test: ") << _testSrcDirLineEdit->text() << "|" << _testDestDirLineEdit->text();

    if(!PathHelper::copyWholeDirectory(_testSrcDirLineEdit->text(), _testDestDirLineEdit->text(), false, PathHelper::SHM_UseAsFile)) {
        WLog("Copy FAILED!");
    }
    else {
        DLog(" -> copy test SUCCESS!");
    }

    DLog(" -> end of COPY test");
}

void MainWindow::_startDeleteTest()
{
    DLog("-- start DELETE test: ") << _testSrcDirLineEdit->text();

    if(!PathHelper::deleteThisDirectoryAndEverythingBelow(_testSrcDirLineEdit->text())) {
        WLog("delete FAILED!");
    }
    else {
        DLog(" - delete test SUCCESS");
    }

    DLog(" -> end of DELETE test");
}
