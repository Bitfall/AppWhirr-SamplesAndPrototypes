#include "mainwindow.h"

#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWebView>
#include <QWebSettings>
#include <QPushButton>
#include <QTextEdit>
#include <QScrollArea>
#include <QWebFrame>

#include <QPixmap>

#include "Common/guiconfigurationmanager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent, Qt::FramelessWindowHint | Qt::CustomizeWindowHint)
{
    _guiConfManager = new GuiConfigurationManager(QString(":/GuiConf"), this);

    QWidget *mainCentralWidget = new QWidget;
    this->setCentralWidget(mainCentralWidget);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainCentralWidget->setLayout(mainLayout);

    QScrollArea *scrollArea = new QScrollArea;
    scrollArea->setFrameShape(QFrame::NoFrame);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet(_guiConfManager->getStyleForId("ScrollBar/Default/GrayGreen/style"));

    QWidget *videoLineWidget = new QWidget;
    videoLineWidget->setObjectName("videoBackgroundWidget");
    videoLineWidget->setStyleSheet(QString("QWidget#videoBackgroundWidget {"
                                           "background-color: #cccccc;"
                                           "background-image: none;"
                                           "border-style: solid;"
                                           "border-width: 1px;"
                                           "border-color: #666666;"
                                           "border-radius: 5px;}"));
    _videoLineLayout = new QHBoxLayout;
    videoLineWidget->setLayout(_videoLineLayout);


    _webView = this->_createWebView();
//    _webView->setAttribute(
//    _webView->setParent(this);
//    _webView->setAttribute(Qt::WA_TranslucentBackground, false);
//    _webView->setWindowFlags(Qt::Window | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);
    _webView->setHtml("");
    _currHtmlContentIndex = 1;
//    _webView->setHtml("<body style=\"margin:0; padding:0;\"><p>HELLO WORLD</p><iframe src=\"http://www.youtube.com/embed/" + youTubeVideoID + "?rel=0\" width=550 height=343 frameborder=0></iframe><body>");

    _videoLineLayout->addWidget(new QTextEdit);
//    _videoLineLayout->addWidget(_webView, 0, Qt::AlignHCenter);
    _videoPlaceLayout = new QVBoxLayout;
    _webViewPlaceHolderWidget = new QWidget;
    _webViewPlaceHolderWidget->setFixedSize(560, 360);
    _webViewPlaceHolderWidget->hide();
    _videoPlaceLayout->addWidget(_webView, 0, Qt::AlignHCenter);
//    _videoPlaceLayout->addWidget(_webViewPlaceHolderWidget, 0, Qt::AlignHCenter);
    _videoLineLayout->addLayout(_videoPlaceLayout);
    _videoLineLayout->addWidget(new QTextEdit);


    scrollArea->setWidget(videoLineWidget);
    mainLayout->addWidget(scrollArea);
//    mainLayout->addWidget(videoLineWidget);

//    webView->hide();

    QPushButton *toggleWebviewVisibility = new QPushButton(tr("Show/hide webview"));
    connect(toggleWebviewVisibility, SIGNAL(clicked()), this, SLOT(_showHideWebview()));
    mainLayout->addWidget(toggleWebviewVisibility);

    _webView->setAttribute(Qt::WA_TranslucentBackground, false);
    _webView->setAttribute(Qt::WA_NoSystemBackground, false);
    _webView->setAttribute(Qt::WA_OpaquePaintEvent, false);
    _webView->setAutoFillBackground(true);
//    _webView->setWindowFlags(Qt::Dialog | Qt::CustomizeWindowHint | Qt::FramelessWindowHint);

    //
    _testCoverWidget = new QWidget(this);
    _testCoverWidget->setStyleSheet("QWidget {background-color:#ff00ff;}");
    _testCoverWidget->hide();

//    this->setAttribute(Qt::WA_TranslucentBackground, true);

    this->resize(1000, 600);
}

MainWindow::~MainWindow()
{

}

void MainWindow::_showHideWebview()
{
    DLog("-show/hide or switch-content: ") << _currHtmlContentIndex;
    if(_currHtmlContentIndex == 0) {
        _webView->hide();
        _webView->setHtml("<body><p>Content 1</p></body>");

//        _testCoverWidget->show();
//        _testCoverWidget->raise();
    }
    else if(_currHtmlContentIndex == 1) {

        _webView->show();
        _webView->raise();
//        _testCoverWidget->raise();
//        _testCoverWidget->hide();

//        QLayoutItem *child;
//        while ((child = _videoPlaceLayout->itemAt(0)) != NULL) {
//            DLog("child");
//            QWidget *widgetChild = child->widget();
//            if(widgetChild != NULL) {
//                DLog("delete: ") << widgetChild->objectName();
//                _videoPlaceLayout->removeWidget(widgetChild);
//                AW_QOBJECT_SAFE_DELETE( widgetChild );
//            }
//            else {
//                DLog("NOT a widget");
//                _videoPlaceLayout->removeItem(child);
//            }
//        }

//        _webView = this->_createWebView();
        _videoPlaceLayout->addWidget(new QPushButton);
//        _videoPlaceLayout->addWidget(_webView, 0, Qt::AlignHCenter);
//        _videoPlaceLayout->addWidget(new QPushButton);

        _webView->settings()->setAttribute(QWebSettings::PluginsEnabled, true);
        QString youTubeVideoID = "HoRH8SByviw";
//        webView->setHtml("<body style=\"margin:0; padding:0;\"><p>HELLO WORLD</p><iframe src=\"http://www.youtube.com/embed/" + youTubeVideoID + "?rel=0\" width=550 height=343 frameborder=0></iframe><body>");
        _webView->setHtml("<iframe src=\"http://www.youtube.com/embed/" + youTubeVideoID + "?rel=0\" width=550 height=343 frameborder=0></iframe>");
//        webView->setHtml("<body><p>Hello world!</p></body>");
//        _webView->show();

//        _webView->setFocusPolicy(Qt::NoFocus);

//        this->_adjustWebViewGeometry();
    }

    _currHtmlContentIndex++;
    if(_currHtmlContentIndex >= 2) {
        _currHtmlContentIndex = 0;
    }
}

void MainWindow::resizeEvent(QResizeEvent *e)
{
//    _testCoverWidget->setGeometry(this->geometry());
//    this->_adjustWebViewGeometry();

    QMainWindow::resizeEvent(e);
}

void MainWindow::paintEvent(QPaintEvent *e)
{
//    QPainter painter(this);
//    painter.fillRect(this->rect(), QColor(125, 0, 0, 100));
}

QWebView *MainWindow::_createWebView()
{
    QWebView *webView = new QWebView;
    webView->setObjectName("test web view");

//    webView->settings()->setAttribute(QWebSettings::PluginsEnabled, true);

//    webView->setStyleSheet(QString("QWidget {"
//                                   "background-color: #cccccc;"
//                                   "background-image: none;"
//                                   "border-style: solid;"
//                                   "border-width: 1px;"
//                                   "border-color: #666666;"
//                                   "border-radius: 5px;}"));

    webView->setFixedSize(560, 360);

    webView->setAttribute(Qt::WA_TranslucentBackground, false);
//    webView->setAttribute(Qt::WA_NoSystemBackground, true);
//    webView->setAttribute(Qt::WA_OpaquePaintEvent, true);
//    webView->setAttribute(Qt::WA_PaintOnScreen, true);

    return webView;
}

void MainWindow::_adjustWebViewGeometry()
{
    QRect globalWebViewRect = QRect(_webViewPlaceHolderWidget->mapToGlobal(QPoint(0, 0)), _webViewPlaceHolderWidget->geometry().size());
    _webView->setGeometry(globalWebViewRect);
}
