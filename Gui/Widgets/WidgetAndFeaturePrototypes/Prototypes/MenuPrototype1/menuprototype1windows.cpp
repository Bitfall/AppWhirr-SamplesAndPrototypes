#include "menuprototype1windows.h"

#include <QVBoxLayout>
#include <QtWebKit/QWebView>
#include <QEvent>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QTextEdit>
#include <QApplication>
#include <QPushButton>

#include <QLineEdit>
#include <QMessageBox>

#include "menupresenter.h"
#include "menuitem.h"
#include "menumanager.h"

MenuPrototype1Window::MenuPrototype1Window(QWidget *parent)
    : QMainWindow(parent),
    isControlButtonPressed(false)
{
    this->resize(800, 600);

    QWidget *centralWidget = new QWidget;
    this->setCentralWidget(centralWidget);

    QVBoxLayout *centralLayout = new QVBoxLayout;
    centralWidget->setLayout(centralLayout);

    // menu push button
    QPushButton *menuPushButton = new QPushButton;
    connect(menuPushButton, SIGNAL(clicked()), this, SLOT(switchMenuVisibility()));
    menuPushButton->setText(tr("Show Menu (or optionally Ctrl + Left-Click anywhere in this window)"));
//    menuPushButton->setMaximumWidth(200);
    centralLayout->addWidget(menuPushButton);
    centralLayout->setAlignment(menuPushButton, Qt::AlignLeft);

    //
    // (test) content
#if 1
    testContentWebView = new QWebView;
    testContentWebView->load(QUrl("http://mac.appstorm.net/reviews/music-reviews/cleaning-up-your-music-library-with-tagalicious/"));
    //view->show();
    centralLayout->addWidget(testContentWebView);
    testContentWebView->hide();
//#else
    testContentTextEdit = new QTextEdit;
    centralLayout->addWidget(testContentTextEdit);
#endif

    //
    // menu
    menuPresenter = new MenuPresenter(centralWidget);
    //connect(menuPresenter->getMenuManager(), SIGNAL(itemClickedSignal(MenuItemWidget*)), this, SLOT(switchPageByMenuItem(MenuItemWidget*)));
    //connect(menuPresenter->getMenuManager(), SIGNAL(fillSubItemsToThisItem(MenuItemWidget*)), this, SLOT(fillSubMenuItemsToThisItem(MenuItemWidget*)));
    // create the root menu items
    {
        MenuManagerVertical1 *menuManager = menuPresenter->getMenuManager();
        // my apps
        MenuItemWidget *myAppsItem = new MenuItemWidget("id-MyApps", "My Apps");
        //connect(myAppsItem, SIGNAL(activated()), this, SLOT(testAppMenuItemActivated()));
        connect(myAppsItem, SIGNAL(itemBecomeTheTopActiveOne(MenuItemWidget*)), this, SLOT(switchPageToMyApps(MenuItemWidget*)));
        menuManager->addRootItem(myAppsItem);

        // grab some apps
        MenuItemWidget *grabSomeAppsItem = new MenuItemWidget("id-GrabSomeApps", "Grab some apps");
        connect(grabSomeAppsItem, SIGNAL(itemBecomeTheTopActiveOne(MenuItemWidget*)), this, SLOT(switchPageToGrabSomeApps(MenuItemWidget*)));
        connect(grabSomeAppsItem, SIGNAL(fillSubItemsToThisItem(MenuItemWidget*)), this, SLOT(fillSubMenuItemsToGrabSomeApps(MenuItemWidget*)));
        menuManager->addRootItem(grabSomeAppsItem);

        // settings
        MenuItemWidget *optionsItem = new MenuItemWidget("id-Options", "Options");
        menuManager->addRootItem(optionsItem);

        // anim
        //grabSomeAppsItem->hideChildren();
    }
    menuPresenter->setGeometry(0, 0, 100, 100);
    //menuManager->setContainerWidget(centralWidget);
    /*QSize targetMenuPos = (this->size() - menuManager->size()) / 2;
    menuManager->setGeometry(QRect(QPoint(targetMenuPos.width(), targetMenuPos.height()),
                             menuManager->sizeHint()));*/
    menuPresenter->raise();
    menuPresenter->hide();
    //centralLayout->addWidget(menuManager);
    //menuManager->setAutoFillBackground(true);

    //this->grabKeyboard();
    //this->grabMouse();
    //this->installEventFilter(QCoreApplication::instance());
    QCoreApplication::instance()->installEventFilter(this);
    //this->setFocusPolicy(Qt::StrongFocus);
}

void MenuPrototype1Window::fillSubMenuItemsToGrabSomeApps(MenuItemWidget *menuItem)
{
    MenuManagerVertical1 *menuManager = menuPresenter->getMenuManager();

    QLineEdit *testCustomWidget = new QLineEdit;
    MenuItemWidget *webItem = new MenuItemWidget("id-Web", "Web");
    connect(webItem, SIGNAL(fillSubItemsToThisItem(MenuItemWidget*)), this, SLOT(fillSubMenuItemsToWeb(MenuItemWidget*)));
    menuManager->addChildToItem(webItem, menuItem, testCustomWidget);

    MenuItemWidget *musicItem = new MenuItemWidget("id-Music", "Music");
    menuManager->addChildToItem(musicItem, menuItem);

    QPushButton *customIMWidget = new QPushButton("Push me baby one more time");
    connect(customIMWidget, SIGNAL(clicked()), this, SLOT(testMessageBoxSlot()));
    MenuItemWidget *imItem = new MenuItemWidget("id-IM", "IM");
    menuManager->addChildToItem(imItem, menuItem, customIMWidget);
}

void MenuPrototype1Window::testMessageBoxSlot()
{
    QMessageBox::information(this, "Yeah...", "Yes, very clever. haha.");
}

void MenuPrototype1Window::fillSubMenuItemsToWeb(MenuItemWidget *menuItem)
{
    MenuManagerVertical1 *menuManager = menuPresenter->getMenuManager();

    MenuItemWidget *webNewsItem = new MenuItemWidget("id-WebNews", "News");
    connect(webNewsItem, SIGNAL(fillSubItemsToThisItem(MenuItemWidget*)), this, SLOT(fillSubMenuItemsToWebNews(MenuItemWidget*)));
    menuManager->addChildToItem(webNewsItem, menuItem);
}

void MenuPrototype1Window::fillSubMenuItemsToWebNews(MenuItemWidget *menuItem)
{
    MenuManagerVertical1 *menuManager = menuPresenter->getMenuManager();

    MenuItemWidget *subItem1 = new MenuItemWidget("id-WebNewsSport", "Sport");
    menuManager->addChildToItem(subItem1, menuItem);

    MenuItemWidget *subItem2 = new MenuItemWidget("id-WebNewsEconomy", "Economy");
    menuManager->addChildToItem(subItem2, menuItem);

    MenuItemWidget *subItem3 = new MenuItemWidget("id-WebNewsLife", "Life");
    menuManager->addChildToItem(subItem3, menuItem);

    MenuItemWidget *subItem4 = new MenuItemWidget("id-WebNewsStyle", "Style");
    menuManager->addChildToItem(subItem4, menuItem);
}

void MenuPrototype1Window::switchPageToMyApps(MenuItemWidget *menuItem)
{
    testContentWebView->hide();
    testContentTextEdit->show();
}

void MenuPrototype1Window::switchPageToGrabSomeApps(MenuItemWidget *menuItem)
{
    testContentTextEdit->hide();
    testContentWebView->show();
}

MenuPrototype1Window::~MenuPrototype1Window()
{

}

void MenuPrototype1Window::switchMenuVisibility()
{
    QSize tmpSize = this->rect().size() / 2;
    menuPresenter->switchShowHideStateAnimated(QPoint(tmpSize.width(), tmpSize.height()));
}

#if 1
bool MenuPrototype1Window::event(QEvent *e)
{
    return QMainWindow::event(e);
}

bool MenuPrototype1Window::eventFilter(QObject *o, QEvent *e)
{
    //qDebug("eventFIlter");
    if(e->type() == QEvent::KeyPress)
    {
        QKeyEvent *castedEvent = dynamic_cast<QKeyEvent *>(e);
        //QMouseEvent *castedEvent = dynamic_cast<QMouseEvent *>(e);
        if(castedEvent != NULL)
        {
            if ( castedEvent->isAutoRepeat() )
            {
                return true; // ignore multiple key-press-events
            }

            //if( me->button() == Qt::RightButton )
            /*if(castedEvent->key() == Qt::Key_F)
            {
                qDebug("KeyPress");
            }
            else */if(castedEvent->key() == Qt::Key_Control)
            {
                isControlButtonPressed = true;
                return true;
            }
        }
    }

    else if(e->type() == QEvent::KeyRelease)
    {
        QKeyEvent *castedEvent = dynamic_cast<QKeyEvent *>(e);
        //QMouseEvent *castedEvent = dynamic_cast<QMouseEvent *>(e);
        if(castedEvent != NULL)
        {
            if ( castedEvent->isAutoRepeat() )
            {
                return true; // ignore multiple key-press-events
            }

            //if( me->button() == Qt::RightButton )
            /*if(castedEvent->key() == Qt::Key_F)
            {
                qDebug("KeyRelease");
                menuManager->switchShowHideStateAnimated();
                return true;
            }
            else */if(castedEvent->key() == Qt::Key_Control)
            {
                isControlButtonPressed = false;
                return true;
            }
        }
    }

    else if(e->type() == QEvent::MouseButtonPress)
    {
        QMouseEvent *castedEvent = dynamic_cast<QMouseEvent *>(e);
        if(castedEvent != NULL)
        {
            if(castedEvent->button() == Qt::LeftButton && isControlButtonPressed)
            {
                this->switchMenuVisibility();
                return true;
            }
        }
    }

    return QMainWindow::eventFilter(o, e);
    //return false;
}
#endif
