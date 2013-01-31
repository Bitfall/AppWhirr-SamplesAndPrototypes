#include "prototypebrowserwindow.h"

#include <QVBoxLayout>
#include <QPushButton>
#include <QLabel>

// prototypes
#include "Prototypes/MenuPrototype1/menuprototype1windows.h"
#include "Prototypes/VideoInWebview/videoinwebviewwindow.h"

PrototypeBrowserWindow::PrototypeBrowserWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *mainCentralWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainCentralWidget->setLayout(mainLayout);
    this->setCentralWidget(mainCentralWidget);

    QLabel *instructionsLabel = new QLabel(tr("Create a button and a separate Window for every prototype."));
    mainLayout->addWidget(instructionsLabel);

    QPushButton *menuPrototype1Button = new QPushButton(tr("Menu Prototype 1"));
    connect(menuPrototype1Button, SIGNAL(clicked()), this, SLOT(presentMenuPrototype1()));
    mainLayout->addWidget(menuPrototype1Button);

    QPushButton *videoInWebviewButton = new QPushButton(tr("Video in Webview"));
    connect(videoInWebviewButton, SIGNAL(clicked()), this, SLOT(presentVideoInWebviewButton()));
    mainLayout->addWidget(videoInWebviewButton);
}

void PrototypeBrowserWindow::presentMenuPrototype1()
{
    MenuPrototype1Window *window = new MenuPrototype1Window(this);
    window->showNormal();
}

void PrototypeBrowserWindow::presentVideoInWebviewButton()
{
    VideoInWebviewWindow *window = new VideoInWebviewWindow(this);
    window->showNormal();
}
