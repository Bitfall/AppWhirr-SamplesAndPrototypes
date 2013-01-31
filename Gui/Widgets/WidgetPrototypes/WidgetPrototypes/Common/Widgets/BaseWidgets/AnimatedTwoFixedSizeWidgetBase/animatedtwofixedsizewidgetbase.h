#ifndef ANIMATEDTWOFIXEDSIZEWIDGETBASE_H
#define ANIMATEDTWOFIXEDSIZEWIDGETBASE_H

#include <QWidget>
#include <QSizeF>

class AnimatedTwoFixedSizeWidgetBase : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QSizeF currFixedSize READ getCurrFixedSize WRITE setCurrFixedSize)
public:
    explicit AnimatedTwoFixedSizeWidgetBase(QSize collapsedSize, QSize expandedSize, bool isExpandedByDefault, QWidget *parent = 0);

    QSize sizeHint() const;

    void switchToExpandedState();
    void switchToCollapsedState();

    bool getIsExpanded() const;

    QSizeF getCurrFixedSize() const;
    void setCurrFixedSize(QSizeF newFixedSize);

signals:
    //
    // connected to the state-machine -> emit this to expand
    void _switchToExpandedStateSignal();
    //
    // connected to the state-machine -> emit this to collapse
    void _switchToCollapsedStateSignal();

public slots:

private:
    bool isExpanded;
    QSizeF _currFixedSize;
};

#endif // ANIMATEDTWOFIXEDSIZEWIDGETBASE_H
