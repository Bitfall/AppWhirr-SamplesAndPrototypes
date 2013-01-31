#include "magnetpoint.h"

#include <QResizeEvent>

MagnetPoint::MagnetPoint(QWidget *parent) :
    QWidget(parent)
{
}

void MagnetPoint::resizeEvent(QResizeEvent *e) {
    Q_EMIT positionChanged(this);

    QWidget::resizeEvent(e);
}

QPointF MagnetPoint::getPosition() const {
    float x = this->rect().x() + ( (float)this->rect().width() / 2.0f );
    float y = this->rect().y() + ( (float)this->rect().height() / 2.0f );

    return QPointF(x, y);
}
