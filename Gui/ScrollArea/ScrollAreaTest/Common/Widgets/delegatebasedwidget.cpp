#include "delegatebasedwidget.h"

#include <QResizeEvent>
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>

DelegateBasedWidget::DelegateBasedWidget(QWidget *parent) :
    QWidget(parent)
{
}

void DelegateBasedWidget::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);

    Q_EMIT resizeHappened(e);
}

void DelegateBasedWidget::paintEvent(QPaintEvent *e)
{
    // must be provided for widgets inherits directly from QWidget if you want to style it with css
    //  check QWidget section here: http://doc.qt.nokia.com/4.7-snapshot/stylesheet-reference.html

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);

//    QWidget::paintEvent(e);
}

