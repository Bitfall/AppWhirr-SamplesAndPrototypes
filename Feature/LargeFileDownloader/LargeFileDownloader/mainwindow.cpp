#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QThreadPool>
#include <QFile>

#include "Common/Communication/resourcedownloadstreamtofile.h"
#include "Common/Communication/resourcedownloadstreamtomemory.h"
#include "Common/File/streamtofilemanager.h"

using namespace AW::Common::Communication;
using namespace AW::Common::Utils;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(startResourceDownload()));

    _resourceDownloader = new ResourceDownloadStreamToFile(NULL, 5, this);
    connect(_resourceDownloader, SIGNAL(resourceDownloadProgressForUrl(int,QUrl)), this, SLOT(_downloadProgressForUrl(int,QUrl)));
    connect(_resourceDownloader, SIGNAL(resourceDownloadFailedForUrl(QUrl)), this, SLOT(_resourceDownloadFailedForUrl(QUrl)));
    connect(_resourceDownloader, SIGNAL(resourceDownloadFinishedWithSuccess(QUrl)), this, SLOT(_finishedResourceDownloading(QUrl)));
    connect(_resourceDownloader, SIGNAL(finishedWithAllResourceDownloads()), this, SLOT(_allResourceDownloadFinished()));

    _resourceDownloaderToMemory = new ResourceDownloadStreamToMemory(NULL, 5, this);
    connect(_resourceDownloaderToMemory, SIGNAL(resourceDownloadProgressForUrl(int,QUrl)), this, SLOT(_memory_downloadProgressForUrl(int,QUrl)));
    connect(_resourceDownloaderToMemory, SIGNAL(resourceDownloadFailedForUrl(QUrl)), this, SLOT(_memory_resourceDownloadFailedForUrl(QUrl)));
    connect(_resourceDownloaderToMemory, SIGNAL(resourceDownloadFinishedWithSuccess(QUrl,QByteArray)), this, SLOT(_memory_finishedResourceDownloading(QUrl,QByteArray)));
    connect(_resourceDownloaderToMemory, SIGNAL(finishedWithAllResourceDownloads()), this, SLOT(_memory_allResourceDownloadFinished()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startResourceDownload()
{
    QString urlString = ui->lineEdit->text();
    QUrl downloadUrl(urlString);

    // - to file
//    if( !_resourceDownloader->addAndInitializeResourceDownloadRequest(downloadUrl, ui->lineEdit_2->text(), true) ) {
//        QMessageBox::warning(this, "Error", "Cannot add the resource");
//        return;
//    }
//    _resourceDownloader->startDownloadingResources();


    // - to memory
    _resourceDownloaderToMemory->addResourceDownloadRequest(downloadUrl);
    _resourceDownloaderToMemory->startDownloadingResources();
}

void MainWindow::_downloadProgressForUrl(int percent, QUrl url)
{
//    DLog(" download percent: ") << percent << "%";
    ui->label->setText(QString("[%1% done] %2").arg(percent).arg(url.path()));
}

void MainWindow::_resourceDownloadFailedForUrl(QUrl url)
{
    WLog("Download FAILED for url:") << url;
    QMessageBox::information(this, "Error", "Resource download failed: " + url.path());
}

void MainWindow::_finishedResourceDownloading(QUrl url)
{
    DLog("Download success for url:") << url;
    QMessageBox::information(this, "Finished", "Stream to file - Success: " + url.path());
}

void MainWindow::_allResourceDownloadFinished()
{
    DLog("All resource downloads finished");
}


// - to memory

void MainWindow::_memory_downloadProgressForUrl(int percent, QUrl url)
{
    ui->label->setText(QString("[%1% done] %2").arg(percent).arg(url.path()));
}

void MainWindow::_memory_resourceDownloadFailedForUrl(QUrl url)
{
    WLog("Download FAILED for url:") << url;
    QMessageBox::information(this, "Error", "Resource download failed: " + url.path());
}

void MainWindow::_memory_finishedResourceDownloading(QUrl url, QByteArray resourceBytes)
{
    DLog("Download success for url:") << url;
    QMessageBox::information(this, "Finished", "Stream to file - Success: " + url.path() + " | byte-size: " + QString::number(resourceBytes.size()));
}

void MainWindow::_memory_allResourceDownloadFinished()
{
    DLog("All resource downloads finished");
}

//void MainWindow::_allRequestsFinished()
//{
//    DLog("All requests finished");
//}

//void MainWindow::_streamToFileFailedWithError(QString filePath, QString errorMessage)
//{
//    QMessageBox::information(this, "Error", "Stream to file failed with error: " + errorMessage + " Path: " + filePath);
//}

//void MainWindow::_streamToFileFinished(QString filePath)
//{
//    QMessageBox::information(this, "Finished", "Stream to file - Success! " + filePath);
//}
