#include "animatedtwofixedsizewidgetbase.h"

// animation
#include <QStateMachine>
#include <QPropertyAnimation>

//
#include <QStyleOption>
#include <QPaintEvent>
#include <QPainter>

// utility
#include <QDebug>
#include "Common/Helpers/qsizehelper.h"

AnimatedTwoFixedSizeWidgetBase::AnimatedTwoFixedSizeWidgetBase(int sizeChangeDurationMilliseconds, QSize collapsedSize, QSize expandedSize, bool isExpandedByDefault, bool isSetWidth, bool isSetHeight, QWidget *parent) :
    QWidget(parent),
    isExpanded(isExpandedByDefault),
    _currFixedSize(QSize(0,0)),
    isSetOnlyMinimumSize(false),
    _isSetWidth(isSetWidth),
    _isSetHeight(isSetHeight),
    _sizeChangeDurationMilliseconds(sizeChangeDurationMilliseconds)
{
//    qDebug() << "Min: " << collapsedSize << " Max: " << expandedSize;
    if(isExpandedByDefault) {
        this->_currFixedSize = expandedSize;
    } else {
        this->_currFixedSize = collapsedSize;
    }

    // fixed size
    this->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
//    this->setFixedSize(this->getCurrFixedSize());

    // state machine

    // expand / collapse
    QStateMachine *machine = new QStateMachine();
    QState *state1 = new QState(machine);
    QState *state2 = new QState(machine);

    state1->assignProperty(this, "currFixedSize", collapsedSize);
    state2->assignProperty(this, "currFixedSize", expandedSize);

    state1->addTransition(this, SIGNAL(_switchToExpandedStateSignal()), state2);
    state2->addTransition(this, SIGNAL(_switchToCollapsedStateSignal()), state1);


    // and add a default animation
    QPropertyAnimation *defaultAnim = new QPropertyAnimation(this, "currFixedSize");
    defaultAnim->setDuration(sizeChangeDurationMilliseconds);
    defaultAnim->setEasingCurve(QEasingCurve::OutExpo);
    machine->addDefaultAnimation(defaultAnim);

    connect(machine, SIGNAL(started()), this, SLOT(stateChangeStarted()));
//    connect(machine, SIGNAL(propertiesAssigned()), this, SLOT(stateChangeFinished()));
    connect(machine, SIGNAL(finished()), this, SLOT(stateChangeFinished()));

    if(isExpandedByDefault) {
        machine->setInitialState(state2);
    } else {
        machine->setInitialState(state1);
    }
    machine->start();

    if(!isExpandedByDefault) {
        if(collapsedSize.width() < 5 || collapsedSize.height() < 5) {
            this->hide();
        }
    }
}

void AnimatedTwoFixedSizeWidgetBase::_setIsSetOnlyMinimumSize(bool value)
{
    this->isSetOnlyMinimumSize = value;
}

void AnimatedTwoFixedSizeWidgetBase::_setIsSetWidth(bool value) {
    this->_isSetWidth = value;
}

void AnimatedTwoFixedSizeWidgetBase::_setIsSetHeight(bool value) {
    this->_isSetHeight = value;
}

void AnimatedTwoFixedSizeWidgetBase::stateChangeStarted()
{

}

void AnimatedTwoFixedSizeWidgetBase::stateChangeFinished()
{
    if(this->getCurrFixedSize().width() < 5 || this->getCurrFixedSize().height() < 5) {
        // the widget is so small that we can hide it
        this->hide();
    }
}

QSize AnimatedTwoFixedSizeWidgetBase::sizeHint() const
{
    QSizeF s = this->getCurrFixedSize();
    QSize intBasedSize = QSizeHelper::normalizedIntBasedSizeFromFloatBasedSize(s);
//    qDebug() << "sizeHint: " << intBasedSize;
    return intBasedSize;
}

QSizeF AnimatedTwoFixedSizeWidgetBase::getCurrFixedSize() const
{
//    qDebug() << "Get FSize: " << this->_currFixedSize;
    return this->_currFixedSize;
}

void AnimatedTwoFixedSizeWidgetBase::setCurrFixedSize(QSizeF newFixedSize)
{
//    qDebug() << "FSize: " << newFixedSize;
    this->_currFixedSize = newFixedSize;

    QSize currSizeInt = QSizeHelper::normalizedIntBasedSizeFromFloatBasedSize(newFixedSize);
    if(this->_isSetWidth) {
        this->setMinimumWidth(currSizeInt.width());
    }
    if(this->_isSetHeight) {
        this->setMinimumHeight(currSizeInt.height());
    }

    if(!this->isSetOnlyMinimumSize) {
//        this->setMaximumSize(QSizeHelper::normalizedIntBasedSizeFromFloatBasedSize(newFixedSize));

        if(this->_isSetWidth) {
            this->setMaximumWidth(currSizeInt.width());
        }
        if(this->_isSetHeight) {
            this->setMaximumHeight(currSizeInt.height());
        }
    }

//    this->updateGeometry();
}

// slot
void AnimatedTwoFixedSizeWidgetBase::switchToExpandedState()
{
    if(this->isExpanded) {
        // already expanded
        return;
    }

    this->show();
    this->isExpanded = true;
    Q_EMIT _switchToExpandedStateSignal();
}

// slot
void AnimatedTwoFixedSizeWidgetBase::switchToCollapsedState()
{
    if(!this->isExpanded) {
        // already collapsed
        return;
    }
    this->isExpanded = false;
    Q_EMIT _switchToCollapsedStateSignal();
}

bool AnimatedTwoFixedSizeWidgetBase::getIsExpanded() const
{
    return this->isExpanded;
}

void AnimatedTwoFixedSizeWidgetBase::paintEvent(QPaintEvent *e)
{
    // must be provided for widgets inherits directly from QWidget if you want to style it with css
    //  check QWidget section here: http://doc.qt.nokia.com/4.7-snapshot/stylesheet-reference.html

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
