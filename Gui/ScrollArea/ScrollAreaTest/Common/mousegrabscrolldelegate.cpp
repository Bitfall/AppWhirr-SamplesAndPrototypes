#include "mousegrabscrolldelegate.h"

#include <QMouseEvent>
#include <QScrollArea>
#include <QScrollBar>
#include <QDebug>
#include <QPropertyAnimation>
#include <QTimer>

#include <math.h>

MouseGrabScrollDelegate::MouseGrabScrollDelegate(int grabScrollAdjustmentIntervalMilliseconds, float grabScrollSpeed, int grabScrollTreshold, float grabDropSlowdownScale, QObject *parent) :
    QObject(parent),
    grabScrollInProgressFlag(false),
    grabScrollMovedMoreThanClickThreasholdFlag(false),
    targetScrollArea(NULL),

    _grabScrollSpeed(grabScrollSpeed),
    _grabScrollTreshold(grabScrollTreshold),
    _grabDropSlowdownScale(grabDropSlowdownScale)
{
    scrollDropAnimation = new QPropertyAnimation(this, "_scrollDroppedForce", this);
    grabScrollAdjustmentTimer = new QTimer(this);
    grabScrollAdjustmentTimer->setInterval(grabScrollAdjustmentIntervalMilliseconds);
    grabScrollAdjustmentTimer->stop();
    connect(grabScrollAdjustmentTimer, SIGNAL(timeout()), this, SLOT(grabScrollAdjustmentTimerTimeout()));
}

bool MouseGrabScrollDelegate::handleMouseButtonPressEvent(QMouseEvent *e)
{
    if(targetScrollArea == NULL)
    {
        qDebug("No target scroll-area defines");
        return false;
    }

    mouseScrollStartPos = e->globalPos();
    grabScrollAdjustmentMouseScrollPosition = mouseScrollStartPos;
    horizontalScrollStartValue = targetScrollArea->horizontalScrollBar()->value();
    verticalScrollStartValue = targetScrollArea->verticalScrollBar()->value();
    grabScrollInProgressFlag = true;
    grabScrollMovedMoreThanClickThreasholdFlag = false;

    // restart the timer
    grabScrollForceCalculationElapsedTimer.restart();

    scrollDropAnimation->stop();

    // start the adjustment timer
    grabScrollAdjustmentTimer->start();

    return true;
}


int MouseGrabScrollDelegate::calculateScrollMoveFromMouseMove(int mouseMoveDistance)
{
    return ceil( ((float)mouseMoveDistance) * _grabScrollSpeed );
}

bool MouseGrabScrollDelegate::handleMouseMoveEvent(QMouseEvent *e)
{
    if(targetScrollArea == NULL)
    {
        qDebug("No target scroll-area defines");
        return false;
    }

    if(grabScrollInProgressFlag)
    {
        if( !grabScrollMovedMoreThanClickThreasholdFlag &&
            (abs(mouseScrollStartPos.x() - e->globalPos().x()) > _grabScrollTreshold ||
            abs(mouseScrollStartPos.y() - e->globalPos().y()) > _grabScrollTreshold) )
        {
            grabScrollMovedMoreThanClickThreasholdFlag = true;
        }

        //int mouseMovedInX = ceil( ((float)(mouseScrollStartPos.x() - e->globalPos().x())) * GuiConfigurations::mouseGrabScrollSpeed() );
        int mouseMovedInX = calculateScrollMoveFromMouseMove(mouseScrollStartPos.x() - e->globalPos().x());
        int scrollPosX = horizontalScrollStartValue + mouseMovedInX;
        targetScrollArea->horizontalScrollBar()->setValue(scrollPosX);

        int mouseMovedInY = calculateScrollMoveFromMouseMove(mouseScrollStartPos.y() - e->globalPos().y());
        int scrollPosY = verticalScrollStartValue + mouseMovedInY;
        targetScrollArea->verticalScrollBar()->setValue(scrollPosY);

        return true;
    }

    return false;
}

void MouseGrabScrollDelegate::grabScrollAdjustmentTimerTimeout()
{
    //QPoint mouseMoveDistance = mouseScrollStartPos - e->globalPos();
    grabScrollAdjustmentMouseScrollPosition = QCursor::pos();
//    qDebug() << "cursor pos" << grabScrollAdjustmentMouseScrollPosition;
}

void MouseGrabScrollDelegate::doSmoothDropScroll(int scrollDistanceX, int scrollDistanceY)
{
    // stop previous if any
    scrollDropAnimation->stop();

    // do the new
    scrollDropHorizontalScrollStartValue = targetScrollArea->horizontalScrollBar()->value();
    scrollDropHorizontalScrollEndValue = scrollDropHorizontalScrollStartValue + scrollDistanceX;

    scrollDropVerticalScrollStartValue = targetScrollArea->verticalScrollBar()->value();
    scrollDropVerticalScrollEndValue = scrollDropVerticalScrollStartValue + scrollDistanceY;

    scrollDropAnimation->setDuration(1000);
    scrollDropAnimation->setEasingCurve(QEasingCurve::OutExpo); // InOutQuad, OutExpo
    scrollDropAnimation->setStartValue(0);
    scrollDropAnimation->setEndValue(1);
    scrollDropAnimation->start();
}

bool MouseGrabScrollDelegate::handleMouseButtonReleaseEvent(QMouseEvent *e)
{
    if(targetScrollArea == NULL)
    {
        qDebug("No target scroll-area defines");
        return false;
    }

    // stop the adjustment timer
    grabScrollAdjustmentTimer->stop();


    grabScrollInProgressFlag = false;
    if( !grabScrollMovedMoreThanClickThreasholdFlag ) {
        return false;
    }

    QPoint mouseMoveFromLastAdjustmentPositionDistance = grabScrollAdjustmentMouseScrollPosition - e->globalPos();
    if(mouseMoveFromLastAdjustmentPositionDistance.x() != 0)
    {
        float elapsedSecs = ((float)grabScrollForceCalculationElapsedTimer.elapsed()) / 1000;
        qDebug() << elapsedSecs;

        float moveSpeedX = (1.0f / elapsedSecs) * (float)mouseMoveFromLastAdjustmentPositionDistance.x();
        moveSpeedX *= _grabDropSlowdownScale;
        //float moveSpeedX = -50;
        qDebug() << "movespeed" << moveSpeedX;

        float moveSpeedY = (1.0f / elapsedSecs) * (float)mouseMoveFromLastAdjustmentPositionDistance.y();
        moveSpeedY *= _grabDropSlowdownScale;

        this->doSmoothDropScroll(moveSpeedX, moveSpeedY);
    }

    return true;
}

void MouseGrabScrollDelegate::setTargetScrollArea(QScrollArea *scrollArea)
{
    this->targetScrollArea = scrollArea;
}

float MouseGrabScrollDelegate::_getScrollDroppedForce() const
{
    return _scrollDroppedForce;
}

void MouseGrabScrollDelegate::_setScrollDroppedForce(float force)
{
    _scrollDroppedForce = force;

#if 1
    float scrollDiffX = (scrollDropHorizontalScrollEndValue - scrollDropHorizontalScrollStartValue);
    scrollDiffX *= force;
    targetScrollArea->horizontalScrollBar()->setValue(scrollDropHorizontalScrollStartValue + scrollDiffX);

    float scrollDiffY = (scrollDropVerticalScrollEndValue - scrollDropVerticalScrollStartValue);
    scrollDiffY *= force;
    targetScrollArea->verticalScrollBar()->setValue(scrollDropVerticalScrollStartValue + scrollDiffY);
#endif
}
