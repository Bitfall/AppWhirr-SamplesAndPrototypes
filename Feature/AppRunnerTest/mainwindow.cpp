#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QStringList>
#include "apprunner.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(_runApp()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::_runApp()
{
    QStringList givenArgs = ui->programArgsLineEdit->text().split("|", QString::SkipEmptyParts);
    ui->logTextEdit->setText( AppRunner::runThisApp(ui->programPathLineEdit->text(), ui->workingDirPathLineEdit->text(), givenArgs) );
}
