#include "menupresenter.h"

#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include <QLineEdit>

#include <QDebug>
#include <QEvent>

#include "faderwidget.h"
#include "menumanager.h"
#include "menuitem.h"
#include "menuitemmanagerelement.h"
//#include "menumanager2.h"
//#include "menuitem2.h"

MenuPresenter::MenuPresenter(QWidget *parent) :
        QWidget(parent, Qt::FramelessWindowHint),
        menuManager(NULL)/*,
        containerWidget(NULL),
        isInGrabMode(true)*/
{
    QHBoxLayout *layout = new QHBoxLayout;
    this->setLayout(layout);
    layout->setContentsMargins(25, 25, 25, 25);

    //
    // menu content

#if 0
    QLabel *label = new QLabel;
    label->setText("hehe");
    layout->addWidget(label);

    QLineEdit *le = new QLineEdit;
    le->setText("valami fasza");
    layout->addWidget(le);
#endif

    this->createMenuLayout();


    //
    // background settings
    this->setAttribute(Qt::WA_NoSystemBackground, true);

    this->setFixedSize(300, 500);
    if( !backgroundPixmap.load(QString(":/MenuPrototype1/menuBackgroundPng")) )
    {
        qDebug() << "failed";
    }

    //showHideRatio = 1;
    this->setFocusPolicy(Qt::StrongFocus);
    this->setFocus();
}
void MenuPresenter::createMenuLayout()
{
#if 1 // prototype 1
    QWidget *menuContainerWidget = new QWidget;
    QVBoxLayout *menuContainerLayout = new QVBoxLayout;
    menuContainerWidget->setLayout(menuContainerLayout);
    this->layout()->addWidget(menuContainerWidget);

    menuManager = new MenuManagerVertical1;
    menuManager->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    menuContainerLayout->addWidget(menuManager);

    // menu spacer
    QWidget *menuSpacerWidget = new QWidget;
    menuSpacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    menuContainerLayout->addWidget(menuSpacerWidget);
    menuSpacerWidget->setStyleSheet("background:#7777bb");
#endif

#if 0 // prototype 2
    QWidget *menuContainerWidget = new QWidget;
    QVBoxLayout *menuContainerLayout = new QVBoxLayout;
    menuContainerWidget->setLayout(menuContainerLayout);
    this->layout()->addWidget(menuContainerWidget);
    menuContainerWidget->setMinimumWidth(200);
    menuContainerWidget->setMaximumWidth(200);

    MenuManager2 *menuManager = new MenuManager2;
    menuContainerLayout->addWidget(menuManager);
    menuManager->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);


    // my apps
    MenuItem2 *myAppsItem = new MenuItem2;
    myAppsItem->setTitle("My Apps");
    //connect(myAppsItem, SIGNAL(activated()), this, SLOT(testAppMenuItemActivated()));
    menuManager->addRootItem(myAppsItem);

    // grab some apps
    MenuItem2 *grabSomeAppsItem = new MenuItem2;
    grabSomeAppsItem->setTitle("Grab some apps");
    menuManager->addRootItem(grabSomeAppsItem);

    MenuItem2 *webItem = new MenuItem2;
    webItem->setTitle("Web");
    grabSomeAppsItem->addChildItem(webItem);

    MenuItem2 *musicItem = new MenuItem2;
    musicItem->setTitle("Music");
    //musicItem->showIt();
    //musicItem->hideAnimated();
    grabSomeAppsItem->addChildItem(musicItem);

    MenuItem2 *imItem = new MenuItem2;
    imItem->setTitle("IM");
    grabSomeAppsItem->addChildItem(imItem);

    // settings
    MenuItem2 *settingsItem = new MenuItem2;
    settingsItem->setTitle("Settigns");
    menuManager->addRootItem(settingsItem);

    // anim
    //grabSomeAppsItem->hideChildren();


    // menu spacer
    QWidget *menuSpacerWidget = new QWidget;
    menuSpacerWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    menuContainerLayout->addWidget(menuSpacerWidget);
    menuSpacerWidget->setStyleSheet("background:#7777bb");
#endif
}

MenuManagerVertical1 *MenuPresenter::getMenuManager()
{
    return menuManager;
}

void MenuPresenter::paintEvent(QPaintEvent *e)
{
    QPainter p(this);
    //p.drawPixmap(this->rect(), grabbedPixmap);
    //p.setOpacity(showHideRatio);
    p.drawPixmap(this->rect(), backgroundPixmap);

    //QWidget::paintEvent(e);
}

void MenuPresenter::showAnimated(QPoint targetPos)
{
    lastTargetPos = targetPos;
    //QRect contGeom = containerWidget->geometry();
    QPoint tmpPos = targetPos - QPoint(this->geometry().size().width() / 2, this->geometry().size().height() / 2);
    /*QRect contGeom = QRect(tmpPos, this->geometry().size());
    QSize tmpSize = (contGeom.size() - this->geometry().size()) / 2;
    QPoint animPoint(tmpSize.width(), tmpSize.height());*/
    this->setGeometry(QRect(tmpPos, this->size()));

    qDebug("show!!");
    this->hide();
    FaderWidget *faderWidget = new FaderWidget(this->parentWidget());
    connect(faderWidget, SIGNAL(fadeFinish()), this, SLOT(showAnimationFinished()));
    faderWidget->fadeThisWidgetIn(this);
    faderWidget->show();
}

void MenuPresenter::hideAnimated()
{
    this->hideAnimated(lastTargetPos);
}

void MenuPresenter::hideAnimated(QPoint targetPos)
{
    lastTargetPos = targetPos;
    //QRect contGeom = containerWidget->geometry();
    QPoint tmpPos = targetPos - QPoint(this->geometry().size().width() / 2, this->geometry().size().height() / 2);
    /*QRect contGeom = targetRect;
    QSize tmpSize = (contGeom.size() - this->rect().size()) / 2;
    QPoint animPoint(tmpSize.width(), tmpSize.height());*/
    this->setGeometry(QRect(tmpPos, this->size()));

    qDebug("hide!!");
    this->hide();
    FaderWidget *faderWidget = new FaderWidget(this->parentWidget());
    connect(faderWidget, SIGNAL(fadeFinish()), this, SLOT(hideAnimationFinished()));
    faderWidget->fadeThisWidgetOut(this);
    faderWidget->show();
}

bool MenuPresenter::event(QEvent *e)
{
    if(e->type() == QEvent::FocusOut)
    {
        //this->hideAnimated();
        //this->hide();
        return true;
    }

    return QWidget::event(e);
}

void MenuPresenter::showAnimationFinished()
{
    this->show();
}

void MenuPresenter::hideAnimationFinished()
{
    this->hide();
}

void MenuPresenter::switchShowHideStateAnimated(QPoint targetPos)
{
    if(this->isVisible())
    {
        this->hideAnimated(targetPos);
    }
    else
    {
        this->showAnimated(targetPos);
    }
}

#if 0
void MenuPresenter::setContainerWidget(QWidget *widget)
{
    this->containerWidget = widget;
}
#endif
