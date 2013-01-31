#include "mainwindow.h"

// UI
#include <QTextEdit>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

// database
#include "AppSpec/Database/testdatabasemanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *mainCentralWidget = new QWidget;
    this->setCentralWidget(mainCentralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainCentralWidget->setLayout(mainLayout);

    QTextEdit *instructionsTextEdit = new QTextEdit;
    instructionsTextEdit->setText(tr("The app has a database as a resource. When you push the 'Do magic' button it will copy the database from the resource near to the exe. This makes it writeable. After this it tries to get some informations from the copied database, but it will fail because some columns missing (also there are some unnecessary unused columns as well) - so it will try to repair it: will extend with the required columns and will remove the unnecessary columns, then it will try again and hopefully this time it will succeed. This is it, database repaired at runtime, when request fails."));
    instructionsTextEdit->setReadOnly(true);
    mainLayout->addWidget(instructionsTextEdit);

    QPushButton *doMagicButton = new QPushButton;
    doMagicButton->setText(tr("Do magic!"));
    connect(doMagicButton, SIGNAL(clicked()), this, SLOT(getSomethingFromDatabaseAndCorrectIt()));
    mainLayout->addWidget(doMagicButton);

    _statusTextEdit = new QTextEdit;
    _statusTextEdit->setText(tr("Status will be printed here"));
    _statusTextEdit->setReadOnly(true);
    mainLayout->addWidget(_statusTextEdit);
}

MainWindow::~MainWindow()
{

}

void MainWindow::getSomethingFromDatabaseAndCorrectIt()
{
    DLog("Magic started...");
    TestDatabaseManager *testDatabaseManager = new TestDatabaseManager;
    QList<TestDatabaseManager::TestDatabaseItemModel> resultItems;
    if(testDatabaseManager->getAllItems(resultItems)) {
        _statusTextEdit->append(tr("%1 items returned").arg(resultItems.size()));
    }
    else {
        _statusTextEdit->append(tr("Cannot get items from the database..."));
    }
    delete testDatabaseManager;
    DLog("Magic done!");
}
