#ifndef MOUSEGRABSCROLLDELEGATE_H
#define MOUSEGRABSCROLLDELEGATE_H

#include <QObject>
#include <QElapsedTimer>
#include <QPoint>

QT_BEGIN_NAMESPACE
class QMouseEvent;
class QScrollArea;
class QPropertyAnimation;
class QTimer;
QT_END_NAMESPACE

//
// # usage (default scenario)
//  * to use this delegate you have to set the targetScrollArea
//  * then install eventFilters to every object in the scroll-area
//  * and transfer the mouse pressed, moved and released event here, and use the returned bool value in the eventFilter method for whether to pass it
//  * you can also call the doSmoothDropScroll method directly - e.g. from a mouse-wheel event
//
class MouseGrabScrollDelegate : public QObject
{
    Q_OBJECT
    Q_PROPERTY(float _scrollDroppedForce READ _getScrollDroppedForce WRITE _setScrollDroppedForce)
public:
    explicit MouseGrabScrollDelegate(int grabScrollAdjustmentIntervalMilliseconds, float grabScrollSpeed, int grabScrollTreshold, float grabDropSlowdownScale, QObject *parent = 0);

    //
    // --- interface ---

    bool handleMouseButtonPressEvent(QMouseEvent *e);
    bool handleMouseMoveEvent(QMouseEvent *e);
    bool handleMouseButtonReleaseEvent(QMouseEvent *e);

    void setTargetScrollArea(QScrollArea *scrollArea);
    void doSmoothDropScroll(int scrollDistanceX, int scrollDistanceY);

private Q_SLOTS:
    void grabScrollAdjustmentTimerTimeout();

private:
    int calculateScrollMoveFromMouseMove(int mouseMoveDistance);

    float _getScrollDroppedForce() const;
    void _setScrollDroppedForce(float force);

private:
    QPoint mouseScrollStartPos;
    int horizontalScrollStartValue;
    int verticalScrollStartValue;
    bool grabScrollInProgressFlag;
    bool grabScrollMovedMoreThanClickThreasholdFlag;
    QElapsedTimer grabScrollForceCalculationElapsedTimer;

    QScrollArea *targetScrollArea;
    float _scrollDroppedForce;
    QPropertyAnimation *scrollDropAnimation;
    int scrollDropHorizontalScrollStartValue;
    int scrollDropHorizontalScrollEndValue;
    int scrollDropVerticalScrollStartValue;
    int scrollDropVerticalScrollEndValue;
    QTimer *grabScrollAdjustmentTimer;
    QPoint grabScrollAdjustmentMouseScrollPosition;

    //
    // settings
    float _grabScrollSpeed;
    int _grabScrollTreshold;
    float _grabDropSlowdownScale;
};

#endif // MOUSEGRABSCROLLDELEGATE_H
