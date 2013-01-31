#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QCoreApplication>
#include <QDebug>
#include <QDir>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::renameMyExe()
{
    QString originalAppFilePath = QCoreApplication::applicationFilePath();
    QString newAppFilePath = originalAppFilePath + ".orig";

    qDebug() << "Orig file path: " << originalAppFilePath;
    qDebug() << "New file pat: " << newAppFilePath;

    if(QDir().rename(originalAppFilePath, newAppFilePath)) {
        QMessageBox::information(this, "rename", "rename happened");
    }
    else {
        QMessageBox::warning(this, "rename failed", "rename failed");
    }
}
