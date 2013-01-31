#include "menuitemmanagerelement.h"

#include <QVBoxLayout>

#include <QStateMachine>
#include <QState>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

#include <QPainter>
#include <QTimer>
#include <QApplication>

#include <QDebug>

#include "menuitem.h"
#include "proposehidemenuitemelementevent.h"

MenuItemManagerElementWidget::MenuItemManagerElementWidget(MenuItemWidget *item, QWidget *parent) :
    QWidget(parent),
    highlightBackgroundColor(120, 150, 160),
    backgroundColorRate(0),
    menuItem(item),
    isHideAnimationProposed(false)
{
    // this one is not working, so make it "manually"
    //connect(this, SIGNAL(destroyed(QObject*)), this, SLOT(_willDeleteSlot(QObject*)));

    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    this->setContentsMargins(0, 0, 0, 0);
    this->setAttribute(Qt::WA_NoSystemBackground, true);

    // main layout
    mainLayout = new QVBoxLayout;
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    this->setLayout(mainLayout);

    // add the menu item
    mainLayout->addWidget(menuItem);

    // custom widget area and layout
    QWidget *customWidgetHolderWidget = new QWidget;
    customWidgetHolderWidget->setContentsMargins(0, 0, 0, 0);

    customWidgetHolderLayout = new QVBoxLayout;
    customWidgetHolderLayout->setContentsMargins(0, 0, 0, 0);
    customWidgetHolderLayout->setSpacing(0);
    customWidgetHolderWidget->setLayout(customWidgetHolderLayout);

    mainLayout->addWidget(customWidgetHolderWidget);


    forceRefreshTimer = new QTimer(this);
    forceRefreshTimer->setInterval(33); // about 30 FPS
    connect(forceRefreshTimer, SIGNAL(timeout()), this, SLOT(update()));
    forceRefreshTimer->stop();

    showHideAnimationGroup = new QParallelAnimationGroup(this);

    //
    // show-hide state animation
#if 0
    QStateMachine *showHideStateMachine = new QStateMachine(this);
    QState *showHideStateHidden = new QState(showHideStateMachine);
    QState *showHideStateShown = new QState(showHideStateMachine);

    qDebug() << "size hint" << this->sizeHint();
    showHideStateHidden->assignProperty(this, "maximumSize", QSize(0, 0));
    showHideStateHidden->assignProperty(this, "minimumSize", QSize(0, 0));
    showHideStateShown->assignProperty(this, "maximumSize", this->sizeHint());
    showHideStateShown->assignProperty(this, "minimumSize", this->sizeHint());

    QSignalTransition *t1 = showHideStateHidden->addTransition(this, SIGNAL(_startToShowSignal()), showHideStateShown);
    QSignalTransition *t2 = showHideStateShown->addTransition(this, SIGNAL(_startToHideSignal()), showHideStateHidden);

    QPropertyAnimation *presenterMaxSizeAnim = new QPropertyAnimation(this, "maximumSize");
    presenterMaxSizeAnim->setDuration(1000);
    presenterMaxSizeAnim->setEasingCurve(QEasingCurve::OutExpo); // InOutQuad, OutExpo

    QPropertyAnimation *presenterMinSizeAnim = new QPropertyAnimation(this, "minimumSize");
    presenterMinSizeAnim->setDuration(1000);
    presenterMinSizeAnim->setEasingCurve(QEasingCurve::OutExpo); // InOutQuad, OutExpo

    t1->addAnimation(presenterMaxSizeAnim);
    t1->addAnimation(presenterMinSizeAnim);

    t2->addAnimation(presenterMaxSizeAnim);
    t2->addAnimation(presenterMinSizeAnim);

    connect(showHideStateHidden, SIGNAL(propertiesAssigned()), this, SLOT(hideAnimationEnded()));
    connect(showHideStateShown, SIGNAL(propertiesAssigned()), this, SLOT(showAnimationEnded()));

    showHideStateMachine->setInitialState(showHideStateShown);
    showHideStateMachine->start();
#endif
}

void MenuItemManagerElementWidget::_willDeleteItself()
{
    qDebug("_willDeleteSlot");
    emit willDeleteItselfSignal(this);
}

void MenuItemManagerElementWidget::addChildToLayout(MenuItemManagerElementWidget *child)
{
    connect(child, SIGNAL(willDeleteItselfSignal(MenuItemManagerElementWidget*)), this, SLOT(_removeThisChild(MenuItemManagerElementWidget*)));
    childrenElements << child;
    mainLayout->addWidget(child);
}

void MenuItemManagerElementWidget::_removeThisChild(MenuItemManagerElementWidget *child)
{
    qDebug("--rmv");
    if(child != NULL)
    {
        qDebug("remove child");
        child->disconnect(this, SLOT(_removeThisChild(MenuItemManagerElementWidget*)));
        childrenElements.removeAll(child);
    }
}

QList<MenuItemManagerElementWidget *> MenuItemManagerElementWidget::getChildrenElements()
{
    return childrenElements;
}

void MenuItemManagerElementWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setOpacity(backgroundColorRate);
    painter.fillRect(rect(), highlightBackgroundColor);
}

void MenuItemManagerElementWidget::showImmediatelly(bool isTerminateShowHideAnimation)
{
    if(isTerminateShowHideAnimation) {
        showHideAnimationGroup->stop();
    }

    this->setMinimumSize(this->sizeHint());
    this->show();
    this->update();
}

void MenuItemManagerElementWidget::hideImmediatelly()
{
    //this->setMinimumSize(0);
    this->hide();
    hideAndDeleteAfterAnimated();
}

void MenuItemManagerElementWidget::_showAnimated()
{
#if 0
    if(isHideAnimationProposed)
    {
        //  this is a kinda workaround to allow presenting
        //  a previously-in-the-index-path item which is now
        //  deactivated. Without this the item would hide itself or would stuck in bigger size.
        this->animatedDeactivate();
    }
#endif

    isHideAnimationProposed = false;
#if 1
    if(this->isVisible())
    {
        // already shown, do nothing
        return;
    }

    // stop current animation
    showHideAnimationGroup->stop();
    // and also clear it
    showHideAnimationGroup->clear();

    // now add the new animations

    QPropertyAnimation *showAnimation1 = new QPropertyAnimation(this, "minimumSize");
    showAnimation1->setDuration(500);
    showAnimation1->setEasingCurve(QEasingCurve::OutExpo);
    showAnimation1->setStartValue(QSize(0, 0));
    showAnimation1->setEndValue(this->sizeHint());

    QPropertyAnimation *showAnimation2 = new QPropertyAnimation(this, "maximumSize");
    showAnimation2->setDuration(500);
    showAnimation2->setEasingCurve(QEasingCurve::OutExpo);
    showAnimation2->setStartValue(QSize(0, 0));
    showAnimation2->setEndValue(this->sizeHint());

    showHideAnimationGroup->addAnimation(showAnimation1);
    showHideAnimationGroup->addAnimation(showAnimation2);

    // disconnect every connection
    showHideAnimationGroup->disconnect();
    // and connect the new one
    connect(showHideAnimationGroup, SIGNAL(finished()), this, SLOT(showAnimationEnded()));
    showHideAnimationGroup->start();
#else
    emit _startToShowSignal();
#endif

    this->show();
}

void MenuItemManagerElementWidget::hideAndDeleteAfterAnimated()
{
    isHideAnimationProposed = true;
    QApplication::postEvent(this, new ProposeHideMenuItemElementEvent());
}

bool MenuItemManagerElementWidget::event(QEvent *e)
{
    if(e->type() == ProposeHideMenuItemElementEvent::getCustomEventType())
    {
        if(isHideAnimationProposed)
        {
            _doHideAnimated();
        }

        return true;
    }

    return QWidget::event(e);
}

void MenuItemManagerElementWidget::_doHideAnimated()
{
    isHideAnimationProposed = false;
#if 1
    if(!this->isVisible())
    {
        // already hidden, do nothing
        return;
    }

    // stop current animation
    showHideAnimationGroup->stop();
    // and also clear it
    showHideAnimationGroup->clear();

    // now add the new animations

    QPropertyAnimation *showAnimation1 = new QPropertyAnimation(this, "minimumSize");
    showAnimation1->setDuration(500);
    showAnimation1->setEasingCurve(QEasingCurve::OutExpo);
    showAnimation1->setStartValue(this->size());
    showAnimation1->setEndValue(QSize(0, 0));

    QPropertyAnimation *showAnimation2 = new QPropertyAnimation(this, "maximumSize");
    showAnimation2->setDuration(500);
    showAnimation2->setEasingCurve(QEasingCurve::OutExpo);
    showAnimation2->setStartValue(this->size());
    showAnimation2->setEndValue(QSize(0, 0));

    showHideAnimationGroup->addAnimation(showAnimation1);
    showHideAnimationGroup->addAnimation(showAnimation2);

    // disconnect every connection
    showHideAnimationGroup->disconnect();
    // and connect the new one
    connect(showHideAnimationGroup, SIGNAL(finished()), this, SLOT(hideAnimationEnded()));
    showHideAnimationGroup->start();
#else
    emit _startToHideSignal();
#endif

    // and also deactivate it
    this->deactivateAnimated();
}

MenuItemWidget *MenuItemManagerElementWidget::getRelatedMenuItem()
{
    return menuItem;
}

void MenuItemManagerElementWidget::deactivateAnimated()
{
    QPropertyAnimation *activateAnimation = createActivateAnimation(backgroundColorRate, 0, 500);
    connect(activateAnimation, SIGNAL(finished()), this, SLOT(activateAnimationEnded()));

    forceRefreshTimer->start();

    activateAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    // and also hide it's children
    int childCnt = this->childrenElements.size();
    for(int i = 0; i < childCnt; i++)
    {
        childrenElements[i]->hideAndDeleteAfterAnimated();
    }

    menuItem->_deactivateAnimated();
}

void MenuItemManagerElementWidget::terminateShowHideAnimation()
{
    showHideAnimationGroup->stop();
}

void MenuItemManagerElementWidget::activateWithLevelAnimated(int level)
{
    QPropertyAnimation *activateAnimation = NULL;
    if(level == 0) {
        activateAnimation = createActivateAnimation(backgroundColorRate, 1.0f, 500);
    } else {
        activateAnimation = createActivateAnimation(backgroundColorRate, (0.7f / ((float)(level + 1))), 500);
    }
    connect(activateAnimation, SIGNAL(finished()), this, SLOT(activateAnimationEnded()));

    forceRefreshTimer->start();

    activateAnimation->start(QAbstractAnimation::DeleteWhenStopped);

    // and also present it's children
    int childCnt = this->childrenElements.size();
    for(int i = 0; i < childCnt; i++)
    {
        //qDebug("show child");
#if 1 // moved
        if(childrenElements[i]->isHideAnimationProposed) {
            // terminate it
            //  this is a kinda workaround to allow presenting
            //  a previously-in-the-index-path item which is now
            //  deactivated. Without this the item would hide itself or would stuck in bigger size.
            childrenElements[i]->deactivateAnimated();
            childrenElements[i]->isHideAnimationProposed = false;
        }
#endif

        childrenElements[i]->_showAnimated();
    }

    menuItem->_activateAnimated();
}

QPropertyAnimation *MenuItemManagerElementWidget::createActivateAnimation(float startRate, float endRate, int duration)
{
    QPropertyAnimation *activateAnimation = new QPropertyAnimation(this, "backgroundColorRate");
    activateAnimation->setDuration(duration);
    activateAnimation->setEasingCurve(QEasingCurve::Linear);
    activateAnimation->setStartValue(startRate);
    activateAnimation->setEndValue(endRate);

    return activateAnimation;
}

void MenuItemManagerElementWidget::activateAnimationEnded()
{
    forceRefreshTimer->stop();
    // ensure final update
    this->update();
}

void MenuItemManagerElementWidget::showAnimationEnded()
{
    qDebug("showAnimationEnded");
    this->setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
}

void MenuItemManagerElementWidget::hideAnimationEnded()
{
    qDebug("hideAnimationEnded");
    this->hide();
    //isHideAnimationProposed = false;
    _willDeleteItself();
    this->deleteLater();
}

void MenuItemManagerElementWidget::addCustomWidget(QWidget *customWidget)
{
    customWidgetHolderLayout->addWidget(customWidget);
}

//
// properties
float MenuItemManagerElementWidget::getBackgroundColorRate() const
{
    return backgroundColorRate;
}

void MenuItemManagerElementWidget::setBackgroundColorRate(float value)
{
    backgroundColorRate = value;
}
