#include "mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QWebView>
#include <QPushButton>
#include <QTextEdit>
#include <QProgressBar>
#include <QLineEdit>

//


//
#include <QApplication>
#include <QDesktopServices>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *mainCentralWidget = new QWidget;
    this->setCentralWidget(mainCentralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainCentralWidget->setLayout(mainLayout);

    QPushButton *openWebpageButton = new QPushButton(tr("Open target page"));
    connect(openWebpageButton, SIGNAL(clicked()), this, SLOT(_openInitialWebpage()));
    mainLayout->addWidget(openWebpageButton);

    _targetPageUrlLineEdit = new QLineEdit;
    _targetPageUrlLineEdit->setText("https://appwhirr.com/app/vlc");
    mainLayout->addWidget(_targetPageUrlLineEdit);

    _testWebView = new QWebView;
    connect(_testWebView, SIGNAL(loadStarted()), this, SLOT(_pageLoadStarted()));
    connect(_testWebView, SIGNAL(loadProgress(int)), this, SLOT(_pageLoadProgress(int)));
    connect(_testWebView, SIGNAL(loadFinished(bool)), this, SLOT(_pageLoadFinished(bool)));
    //
    _testWebView->page()->setLinkDelegationPolicy(QWebPage::DelegateAllLinks);
    connect(_testWebView->page(), SIGNAL(linkClicked(QUrl)), this, SLOT(_linkClicked(QUrl)));
    mainLayout->addWidget(_testWebView);

    _pageLoadProgressBar = new QProgressBar;
    _pageLoadProgressBar->setMinimum(0);
    _pageLoadProgressBar->setMaximum(100);
    mainLayout->addWidget(_pageLoadProgressBar);
    _pageLoadProgressBar->hide();


    _logTextEdit = new QTextEdit(tr("Log"));
    mainLayout->addWidget(_logTextEdit);

    this->resize(800, 500);

    // register custom url handled by this app
    QDesktopServices::setUrlHandler("appwhirr", this, "_handleCustomSchemeUrl");
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::_openInitialWebpage()
{
    _logTextEdit->append("Opening webpage: " + _targetPageUrlLineEdit->text());
    _testWebView->setUrl(QUrl(_targetPageUrlLineEdit->text()));
}

void MainWindow::_handleCustomSchemeUrl(QUrl url)
{
    _logTextEdit->append(tr("Custom url: %1").arg(url.toString()));
}

// page loading
void MainWindow::_pageLoadStarted()
{
    _logTextEdit->append(tr("Page loading started..."));
    _pageLoadProgressBar->show();
}

void MainWindow::_pageLoadProgress(int progressPercent)
{
//    _logTextEdit->append(tr("Page load progress: %1%").arg(QString::number(progressPercent)));
    _pageLoadProgressBar->setValue(progressPercent);
}

void MainWindow::_pageLoadFinished(bool isOk)
{
    _logTextEdit->append(tr("Page loaded. Is OK? %1").arg(isOk));
    _pageLoadProgressBar->hide();
}

void MainWindow::_linkClicked(QUrl url)
{
    _logTextEdit->append(tr("Link clicked: %1").arg(url.toString()));
    _logTextEdit->append(tr(" - Url scheme: %1").arg(url.scheme()));
    QDesktopServices::openUrl(url);
}
