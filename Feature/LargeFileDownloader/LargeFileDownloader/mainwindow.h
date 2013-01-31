#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <QHash>

namespace Ui {
class MainWindow;
}

namespace AW {
namespace Common {
//
namespace Communication {
class ResourceDownloadStreamToFile;
class ResourceDownloadStreamToMemory;
}
}
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void startResourceDownload();

    void _downloadProgressForUrl(int percent, QUrl url);
    void _resourceDownloadFailedForUrl(QUrl url);
    void _finishedResourceDownloading(QUrl url);
    void _allResourceDownloadFinished();

    // - to memory
    void _memory_downloadProgressForUrl(int percent, QUrl url);
    void _memory_resourceDownloadFailedForUrl(QUrl url);
    void _memory_finishedResourceDownloading(QUrl url, QByteArray resourceBytes);
    void _memory_allResourceDownloadFinished();

private:
    Ui::MainWindow *ui;

    AW::Common::Communication::ResourceDownloadStreamToFile *_resourceDownloader;
    AW::Common::Communication::ResourceDownloadStreamToMemory *_resourceDownloaderToMemory;
};

#endif // MAINWINDOW_H
