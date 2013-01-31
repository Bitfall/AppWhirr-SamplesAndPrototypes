#include "simpleimagepresenterwidget.h"

#include <QPainter>
#include <QMouseEvent>

SimpleImagePresenterWidget::SimpleImagePresenterWidget(QWidget *parent) :
    QWidget(parent),
    isAutoResizeToImageSize(false)
{
    this->commonInit();
}

SimpleImagePresenterWidget::SimpleImagePresenterWidget(QString imagePath, QWidget *parent) :
    QWidget(parent),
    isAutoResizeToImageSize(false)
{
    this->commonInit();
    this->setImageByPath(imagePath);
}

void SimpleImagePresenterWidget::commonInit()
{
    this->setAttribute(Qt::WA_NoSystemBackground, true);
}

void SimpleImagePresenterWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.drawPixmap(this->rect(), imageToPresent);
}

void SimpleImagePresenterWidget::mousePressEvent(QMouseEvent * event)
{
    if(event->button() == Qt::LeftButton) {
        emit clicked();
        event->accept();
    }

    QWidget::mousePressEvent(event);
}

void SimpleImagePresenterWidget::setImageByPath(QString imagePath) {
    imageToPresent.load(imagePath);

    if(isAutoResizeToImageSize) {
        this->resizeToImageSize();
    }
}

void SimpleImagePresenterWidget::setAutoResizeToImageSize(bool isAutoResize)
{
    isAutoResizeToImageSize = isAutoResize;
    if(isAutoResizeToImageSize) {
        this->resizeToImageSize();
    }
}

void SimpleImagePresenterWidget::resizeToImageSize() {
    if(!imageToPresent.isNull()) {
        this->setFixedSize(imageToPresent.size());
    }
}
