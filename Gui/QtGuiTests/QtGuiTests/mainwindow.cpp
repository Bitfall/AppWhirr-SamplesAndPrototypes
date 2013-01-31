#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "testingform.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    TestingForm *testingForm = new TestingForm;
    testingForm->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
