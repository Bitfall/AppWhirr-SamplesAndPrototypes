#include "mainwindow.h"

#include <QVBoxLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>

//
#include <QDir>
#include <QFileInfo>
#include <QFileInfoList>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *mainCentralWidget =new QWidget;
    this->setCentralWidget(mainCentralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainCentralWidget->setLayout(mainLayout);

    _targetDirToListLineEdit = new QLineEdit;
    _targetDirToListLineEdit->setPlaceholderText(tr("Target dir to list it's content."));
    mainLayout->addWidget(_targetDirToListLineEdit);

    QPushButton *listDirButton = new QPushButton(tr("List given dir's content."));
    connect(listDirButton, SIGNAL(clicked()), this, SLOT(_listDirContent()));
    mainLayout->addWidget(listDirButton);

    _logTextEdit = new QTextEdit;
    mainLayout->addWidget(_logTextEdit);

    this->resize(600, 400);
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::_listDirContent()
{
    _logTextEdit->append("Content of dir: " + _targetDirToListLineEdit->text());

    QDir targetDir(_targetDirToListLineEdit->text());

    QFileInfoList entryInfos = targetDir.entryInfoList(QDir::System | QDir::Hidden | QDir::Dirs | QDir::NoDotAndDotDot/*| QDir::NoSymLinks*/);
    Q_FOREACH(QFileInfo entryInfo, entryInfos) {
        _logTextEdit->append(" - " + entryInfo.absoluteFilePath());
    }
}
