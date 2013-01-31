#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

QT_BEGIN_NAMESPACE
class QWebView;
class QHBoxLayout;
class QVBoxLayout;
QT_END_NAMESPACE

class GuiConfigurationManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void _showHideWebview();

protected:
    void resizeEvent(QResizeEvent *e);
    void paintEvent(QPaintEvent *e);

private:
    QWebView *_createWebView();
    void _adjustWebViewGeometry();

private:
    GuiConfigurationManager *_guiConfManager;
    QWebView *_webView;
    QWidget *_webViewPlaceHolderWidget;
    QHBoxLayout *_videoLineLayout;
    QVBoxLayout *_videoPlaceLayout;

    QWidget *_testCoverWidget;

    int _currHtmlContentIndex;
};

#endif // MAINWINDOW_H
