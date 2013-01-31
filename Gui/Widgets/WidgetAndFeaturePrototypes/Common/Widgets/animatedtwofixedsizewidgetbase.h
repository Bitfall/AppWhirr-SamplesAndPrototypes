#ifndef ANIMATEDTWOFIXEDSIZEWIDGETBASE_H
#define ANIMATEDTWOFIXEDSIZEWIDGETBASE_H

#include <QWidget>
#include <QSizeF>

class AnimatedTwoFixedSizeWidgetBase : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QSizeF currFixedSize READ getCurrFixedSize WRITE setCurrFixedSize)
public:
    explicit AnimatedTwoFixedSizeWidgetBase(int sizeChangeDurationMilliseconds, QSize collapsedSize, QSize expandedSize, bool isExpandedByDefault, bool isSetWidth, bool isSetHeight, QWidget *parent = 0);

    QSize sizeHint() const;

    bool getIsExpanded() const;

    QSizeF getCurrFixedSize() const;
    void setCurrFixedSize(QSizeF newFixedSize);

    //
    // By default both minimum and maximum size will be set, and it's also the prefered way. With this you can set that only minimum size should be changed.
    //  But consider using _setIsSetWidth/Height methods instead!
    void _setIsSetOnlyMinimumSize(bool value);
    void _setIsSetWidth(bool value);
    void _setIsSetHeight(bool value);

public Q_SLOTS:
    void switchToExpandedState();
    void switchToCollapsedState();

Q_SIGNALS:
    //
    // connected to the state-machine -> emit this to expand
    void _switchToExpandedStateSignal();
    //
    // connected to the state-machine -> emit this to collapse
    void _switchToCollapsedStateSignal();

protected:
    void paintEvent(QPaintEvent *e);

private Q_SLOTS:
    void stateChangeStarted();
    void stateChangeFinished();

private:
    bool isExpanded;
    QSizeF _currFixedSize;
    bool isSetOnlyMinimumSize;
    bool _isSetWidth;
    bool _isSetHeight;

    int _sizeChangeDurationMilliseconds;
};

#endif // ANIMATEDTWOFIXEDSIZEWIDGETBASE_H
