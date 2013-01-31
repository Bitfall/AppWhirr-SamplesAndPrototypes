#include "idbasedwidget.h"

#include <QStyleOption>
#include <QPainter>

IdBasedWidget::IdBasedWidget(QString itemId, QWidget *parent) :
    QWidget(parent),
    _itemId(itemId)
{
}

QString IdBasedWidget::getId() const {
    return _itemId;
}

void IdBasedWidget::paintEvent(QPaintEvent *e)
{
    // must be provided for widgets inherits directly from QWidget if you want to style it with css
    //  check QWidget section here: http://doc.qt.nokia.com/4.7-snapshot/stylesheet-reference.html

    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}
