#include "mainwindow.h"

#include <QVBoxLayout>
#include <QWebView>
#include <QWebSettings>
#include <QPushButton>

QString contentOneHtml("<body style=\"margin:0; padding:0;\"><p>HELLO WORLD</p><iframe src=\"http://www.youtube.com/embed/HoRH8SByviw?rel=0\" width=550 height=343 frameborder=0></iframe><body>");
QString contentTwoHtml("<iframe src=\"http://www.youtube.com/embed/WXVU6Tlz8mU?rel=0\" width=550 height=343 frameborder=0></iframe>");

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      isContentOneIsCurrent(true)
{
    QWidget *mainCentralWidget = new QWidget;
    this->setCentralWidget(mainCentralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainCentralWidget->setLayout(mainLayout);

    webView = new QWebView;
    mainLayout->addWidget(webView);

    webView->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
    webView->setHtml(contentOneHtml);

    QPushButton *switchContentButton = new QPushButton(tr("Switch content"));
    connect(switchContentButton, SIGNAL(clicked()), this, SLOT(_switchContent()));
    mainLayout->addWidget(switchContentButton);
}

MainWindow::~MainWindow()
{

}

void MainWindow::_switchContent()
{
    if(isContentOneIsCurrent) {
        webView->setHtml(contentTwoHtml);
        isContentOneIsCurrent = false;
    }
    else {
        webView->setHtml(contentOneHtml);
        isContentOneIsCurrent = true;
    }
}
