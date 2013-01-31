#include "videoinwebviewwindow.h"
#include "ui_videoinwebviewwindow.h"

#include <QNetworkProxyFactory>

VideoInWebviewWindow::VideoInWebviewWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::VideoInWebviewWindow)
{
    ui->setupUi(this);
}

VideoInWebviewWindow::~VideoInWebviewWindow()
{
    delete ui;
}

void VideoInWebviewWindow::on_pushButton_clicked()
{
//    QNetworkProxyFactory::setUseSystemConfiguration (true);
    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
//    QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, false); // disable flash plugin
    QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages, true);
//    QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages, false);
    ui->webView->setHtml(QString("<iframe width=\"425\" height=\"349\" src=\"http://www.youtube.com/embed/3aR27FLbb04\" frameborder=\"0\" allowfullscreen></iframe>"));
}
