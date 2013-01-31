#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include <QUrl>

QT_BEGIN_NAMESPACE
class QTextEdit;
class QWebView;
class QProgressBar;
class QLineEdit;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void _openInitialWebpage();
    void _handleCustomSchemeUrl(QUrl url);

    // webview slots
    void _pageLoadStarted();
    void _pageLoadProgress(int progressPercent);
    void _pageLoadFinished(bool isOk);

    //
    void _linkClicked(QUrl url);

private:
    QLineEdit *_targetPageUrlLineEdit;
    QTextEdit *_logTextEdit;
    QWebView *_testWebView;
    QProgressBar *_pageLoadProgressBar;
};

#endif // MAINWINDOW_H
