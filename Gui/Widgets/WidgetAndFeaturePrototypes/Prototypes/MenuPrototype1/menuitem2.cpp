#include "menuitem2.h"

#include <QEvent>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>

#include <QStateMachine>
#include <QState>
#include <QSignalTransition>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

#include <QPainter>

MenuItem2::MenuItem2(QWidget *parent) :
    QWidget(parent),
    isChildrenCollapsed(false),
    isActivated(false)
{
    this->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    this->setAttribute(Qt::WA_NoSystemBackground, true);

    mainLayout = new QVBoxLayout;
    this->setLayout(mainLayout);


#if 0
    QWidget *spacerWidget = new QWidget;
    spacerWidget->setMinimumWidth(10);
    spacerWidget->setMaximumWidth(10);
    mainLayout->addWidget(spacerWidget);
    spacerWidget->setStyleSheet("background:#bbccbb");
#endif

    QVBoxLayout *contentLayout = mainLayout;

    itemTitleLabel = new QLabel;
    contentLayout->addWidget(itemTitleLabel);

    QWidget *childContainerWidget = new QWidget;
    childLayout = new QVBoxLayout;
    childContainerWidget->setLayout(childLayout);
    contentLayout->addWidget(childContainerWidget);

    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);
    childLayout->setContentsMargins(0, 0, 0, 0);
    childLayout->setSpacing(0);
    childContainerWidget->setContentsMargins(0, 0, 0, 0);
    this->setContentsMargins(0, 0, 0, 0);


/*
#if 0
    this->setMinimumSize(200, 50);
    this->setMaximumSize(200, 50);
#else
    this->setMinimumSize(0, 0);
    this->setMaximumSize(0, 0);
#endif
*/
}

void MenuItem2::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.fillRect(this->rect(), QColor(100, 150, 200));
}

void MenuItem2::setActive(bool state)
{
    this->isActivated = state;
    if(state)
    {
        this->setMinimumHeight(200);
    } else {
        this->setMinimumHeight(50);
    }
}

void MenuItem2::setTitle(QString title)
{
    itemTitleLabel->setText(title);
}

void MenuItem2::addChildItem(MenuItem2 *item)
{
#if 1
    childMenuItems << item;
    childLayout->addWidget(item);
#endif
}

void MenuItem2::showChildren()
{
#if 1
    int childCnt = childMenuItems.size();
    for(int i = 0; i < childCnt; i++)
    {
        childMenuItems[i]->show();
    }
#endif
}

void MenuItem2::hideChildren()
{
#if 1
    int childCnt = childMenuItems.size();
    for(int i = 0; i < childCnt; i++)
    {
        childMenuItems[i]->hide();
    }
#endif
}

void MenuItem2::showAnimated()
{
    QParallelAnimationGroup *animGroup = new QParallelAnimationGroup;

    QPropertyAnimation *showAnimation1 = new QPropertyAnimation(this, "minimumSize");
    showAnimation1->setDuration(1000);
    showAnimation1->setEasingCurve(QEasingCurve::OutExpo);
    showAnimation1->setStartValue(QSize(0, 0));
    showAnimation1->setEndValue(this->sizeHint());

    QPropertyAnimation *showAnimation2 = new QPropertyAnimation(this, "maximumSize");
    showAnimation2->setDuration(1000);
    showAnimation2->setEasingCurve(QEasingCurve::OutExpo);
    showAnimation2->setStartValue(QSize(0, 0));
    showAnimation2->setEndValue(this->sizeHint());

    animGroup->addAnimation(showAnimation1);
    animGroup->addAnimation(showAnimation2);

    animGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

void MenuItem2::hideAnimated()
{
    QParallelAnimationGroup *animGroup = new QParallelAnimationGroup;

    QPropertyAnimation *showAnimation1 = new QPropertyAnimation(this, "minimumSize");
    showAnimation1->setDuration(1000);
    showAnimation1->setEasingCurve(QEasingCurve::OutExpo);
    showAnimation1->setStartValue(this->size());
    showAnimation1->setEndValue(QSize(0, 0));

    QPropertyAnimation *showAnimation2 = new QPropertyAnimation(this, "maximumSize");
    showAnimation2->setDuration(1000);
    showAnimation2->setEasingCurve(QEasingCurve::OutExpo);
    showAnimation2->setStartValue(this->size());
    showAnimation2->setEndValue(QSize(0, 0));

    animGroup->addAnimation(showAnimation1);
    animGroup->addAnimation(showAnimation2);

    animGroup->start(QAbstractAnimation::DeleteWhenStopped);
}

bool MenuItem2::event(QEvent *e)
{
#if 1
    if(e->type() == QEvent::MouseButtonPress)
    {
        emit activated();

        this->showChildren();

        return true;
    }
#endif

    return QWidget::event(e);
}

void MenuItem2::showAnimationEnded()
{
    qDebug("showAnimationEnded");
}

void MenuItem2::hideAnimationEnded()
{
    qDebug("hideAnimationEnded");
}
