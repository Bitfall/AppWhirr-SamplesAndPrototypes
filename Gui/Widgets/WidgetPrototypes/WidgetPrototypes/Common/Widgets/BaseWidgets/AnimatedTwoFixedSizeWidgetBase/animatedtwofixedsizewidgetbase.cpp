#include "animatedtwofixedsizewidgetbase.h"

// animation
#include <QStateMachine>
#include <QPropertyAnimation>

// utility
#include <QDebug>
#include "../../../Helpers/SizeHelper/sizehelper.h"

AnimatedTwoFixedSizeWidgetBase::AnimatedTwoFixedSizeWidgetBase(QSize collapsedSize, QSize expandedSize, bool isExpandedByDefault, QWidget *parent) :
    QWidget(parent),
    isExpanded(isExpandedByDefault),
    _currFixedSize(QSize(0,0))
{
    qDebug() << "Min: " << collapsedSize << " Max: " << expandedSize;
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
    defaultAnim->setDuration(1000);
    defaultAnim->setEasingCurve(QEasingCurve::OutExpo);
    machine->addDefaultAnimation(defaultAnim);

    if(isExpandedByDefault) {
        machine->setInitialState(state2);
    } else {
        machine->setInitialState(state1);
    }
    machine->start();
}

QSize AnimatedTwoFixedSizeWidgetBase::sizeHint() const
{
    QSizeF s = this->getCurrFixedSize();
    QSize intBasedSize = SizeHelper::normalizedIntBasedSizeFromFloatBasedSize(s);
    qDebug() << "sizeHint: " << intBasedSize;
    return intBasedSize;
}

QSizeF AnimatedTwoFixedSizeWidgetBase::getCurrFixedSize() const
{
    qDebug() << "Get FSize: " << this->_currFixedSize;
    return this->_currFixedSize;
}

void AnimatedTwoFixedSizeWidgetBase::setCurrFixedSize(QSizeF newFixedSize)
{
    qDebug() << "FSize: " << newFixedSize;
    this->_currFixedSize = newFixedSize;

    this->setMinimumSize(SizeHelper::normalizedIntBasedSizeFromFloatBasedSize(newFixedSize));
    this->setMaximumSize(SizeHelper::normalizedIntBasedSizeFromFloatBasedSize(newFixedSize));

    this->updateGeometry();
}

void AnimatedTwoFixedSizeWidgetBase::switchToExpandedState()
{
    this->isExpanded = true;
    emit _switchToExpandedStateSignal();
}

void AnimatedTwoFixedSizeWidgetBase::switchToCollapsedState()
{
    this->isExpanded = false;
    emit _switchToCollapsedStateSignal();
}

bool AnimatedTwoFixedSizeWidgetBase::getIsExpanded() const
{
    return this->isExpanded;
}
