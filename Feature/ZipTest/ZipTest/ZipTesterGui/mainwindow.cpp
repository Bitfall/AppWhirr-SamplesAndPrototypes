#include "mainwindow.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

#include "Common/Uncompressor/uncompressor.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *mainCentralWidget = new QWidget;
    this->setCentralWidget(mainCentralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainCentralWidget->setLayout(mainLayout);

    _zipPathLineEdit = new QLineEdit;
    _zipPathLineEdit->setPlaceholderText(tr("Paste the ZIP's path here"));
    mainLayout->addWidget(_zipPathLineEdit);

    _outputPathLineEdit = new QLineEdit;
    _outputPathLineEdit->setPlaceholderText(tr("Paste the OUTPUT directory path here"));
    mainLayout->addWidget(_outputPathLineEdit);

    QPushButton *startUnzipButton = new QPushButton(tr("Start unzip!"));
    connect(startUnzipButton, SIGNAL(clicked()), this, SLOT(_startUnzip()));
    mainLayout->addWidget(startUnzipButton);

    DLog("Test") << "test";
    DLogS << "Num test: " << (789 & 0xFF00) << (789 & 0x00FF);

    this->resize(600, 300);
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::_startUnzip()
{
    DLog("-- unzip --");

    bool isSuccess = Uncompressor::uncompress(_zipPathLineEdit->text(), _outputPathLineEdit->text());

    DLog("-- finished --");
    QMessageBox::information(this, tr("Finished"), tr("Finished with result: %1").arg(isSuccess));
}
