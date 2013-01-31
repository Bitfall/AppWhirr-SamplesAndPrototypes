#include "mainwindow.h"

#include <QLabel>
#include <QScrollArea>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QListView>
#include <QEvent>
#include <QMouseEvent>
#include <QScrollBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    //
    // default, window related
    this->resize(400, 300);

    QWidget *centralWidget = new QWidget;
    QVBoxLayout *mainLayout = new QVBoxLayout;
    centralWidget->setLayout(mainLayout);

    this->setCentralWidget(centralWidget);

    //
    // scroll-area
    scrollArea = new QScrollArea;
    scrollArea->setBackgroundRole(QPalette::Dark);
    mainLayout->addWidget(scrollArea);

    //
    // scroll-area content/container widget
    QWidget *scrollAreaContainer = new QWidget;
    QVBoxLayout *scrollAreaLayout = new QVBoxLayout;
    scrollAreaContainer->setLayout(scrollAreaLayout);
    scrollArea->setWidget(scrollAreaContainer);

    //scrollAreaContainer->setMinimumSize(800, 800);

    //
    // other widgets (contents)
    QLabel *imageLabel = new QLabel;
    QImage image(":test_pic");
    imageLabel->setPixmap(QPixmap::fromImage(image));
    imageLabel->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    imageLabel->setMinimumSize(800, 800);
    imageLabel->setScaledContents(true);

#if 0
    QListView *listView = new QListView;
    listView->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    listView->setMinimumSize(600, 600);
#endif

    scrollAreaLayout->addWidget(imageLabel);
    //mainLayout->addWidget(imageLabel);

    scrollAreaContainer->adjustSize();

    this->installEventFilter(this);

}

MainWindow::~MainWindow()
{

}

void MainWindow::processMouseButtonPressEvent(QObject *obj, QMouseEvent *e)
{
    qDebug("1");
    mouseScrollStartPos = e->pos();
    scrollOffset.setY( scrollArea->verticalScrollBar()->value() );
    scrollOffset.setX( scrollArea->horizontalScrollBar()->value() );
}

void MainWindow::processMouseMoveEvent(QObject *obj, QMouseEvent *e)
{
    qDebug("2");
    int scrollPosY = scrollOffset.y() + mouseScrollStartPos.y() - e->pos().y();
    int scrollPosX = scrollOffset.x() + mouseScrollStartPos.x() - e->pos().x();
    qDebug(QString("Pos: %1").arg(scrollPosY).toAscii());

    scrollArea->verticalScrollBar()->setValue(scrollPosY);
    scrollArea->horizontalScrollBar()->setValue(scrollPosX);
}

void MainWindow::processMouseButtonReleaseEvent(QObject *obj, QMouseEvent *e)
{
    qDebug("3");
}

bool MainWindow::eventFilter(QObject* object, QEvent* event)
{
    if(event->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *me = dynamic_cast<QMouseEvent *>(event);
        if(me)
        {
            processMouseButtonPressEvent(object, me);
            return true;
        }
    }

    if(event->type() == QEvent::MouseButtonRelease)
    {
        QMouseEvent *me = dynamic_cast<QMouseEvent *>(event);
        if(me)
        {
            processMouseButtonReleaseEvent(object, me);
            return true;
        }
    }

    if(event->type() == QEvent::MouseMove)
    {
        QMouseEvent *me = dynamic_cast<QMouseEvent *>(event);
        if(me)
        {
            processMouseMoveEvent(object, me);
            return true;
        }
    }


    return false;
}
