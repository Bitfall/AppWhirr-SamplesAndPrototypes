#include "mainwindow.h"

#include <QHBoxLayout>

#include "horizontalreorderinglayout.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *centralWidget = new QWidget;
    this->setCentralWidget(centralWidget);

    //QHBoxLayout *theLayout = new QHBoxLayout; // test Qt QHBoxLayout

    HighPerformanceHorizontalLayout *theLayout = new HighPerformanceHorizontalLayout;

    centralWidget->setLayout(theLayout);

    // add some test widgets
    for(int i = 0; i < 3; ++i)
    {
        QWidget *testWidget = new QWidget;
        testWidget->setMaximumSize(150, 150);
        testWidget->setMinimumSize(50, 50);
        testWidget->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        testWidget->setStyleSheet("QWidget {background-color:#aabbcc}");
        theLayout->addWidget(testWidget);
    }
}

MainWindow::~MainWindow()
{
}
