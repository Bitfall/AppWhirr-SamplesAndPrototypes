#include "mainwindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QLineEdit>

#include "AppSpec/customappinstallmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *mainCentralWidget = new QWidget;
    this->setCentralWidget(mainCentralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainCentralWidget->setLayout(mainLayout);

    _installFilePathLineEdit = new QLineEdit;
    _installFilePathLineEdit->setPlaceholderText(tr("Specify the custom install xml."));
    mainLayout->addWidget(_installFilePathLineEdit);

    _doTestButton = new QPushButton(tr("Start test."));
    connect(_doTestButton, SIGNAL(clicked()), this, SLOT(startTest()));
    mainLayout->addWidget(_doTestButton);

    _logTextEdit = new QTextEdit;
    mainLayout->addWidget(_logTextEdit);


    //
    //
    _customAppInstallManager = new CustomAppInstallManager(this);
    connect(_customAppInstallManager, SIGNAL(finishedWithSuccess()), this, SLOT(_customAppInstallFinishedWithSuccess()));
    connect(_customAppInstallManager, SIGNAL(finishedWithError(QString)), this, SLOT(_customAppInstallFinishedWithError(QString)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::startTest()
{
    _logTextEdit->append("----- test started ----");
    _customAppInstallManager->performByFile(_installFilePathLineEdit->text());
}

void MainWindow::_customAppInstallFinishedWithSuccess()
{
    _logTextEdit->append(QString("* finished with success"));
}

void MainWindow::_customAppInstallFinishedWithError(QString errorMessage)
{
    _logTextEdit->append(QString("* finished with error: %1").arg(errorMessage));
}
