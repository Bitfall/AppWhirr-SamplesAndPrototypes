#include "crossfaderwidget.h"

#include <QPainter>
#include <QTimer>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

#include <QDebug>

CrossFaderWidget::CrossFaderWidget(QWidget *parent) :
    QWidget(parent)
{
    // gui updater
    {
        guiUpdaterTimer = new QTimer(this);
        guiUpdaterTimer->setInterval(33); // about 30 FPS
        connect(guiUpdaterTimer, SIGNAL(timeout()), this, SLOT(update()));
        guiUpdaterTimer->stop();
    }

    this->setAttribute(Qt::WA_NoSystemBackground, true);

    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->setContentsMargins(0, 0, 0, 0);

    // animation
    {
        fadeAnimation = new QPropertyAnimation(this, "transitionPercentage", this);
        fadeAnimation->setStartValue(0.0f);
        fadeAnimation->setEndValue(1.0f);
        fadeAnimation->setEasingCurve(QEasingCurve::InOutExpo);
        connect(fadeAnimation, SIGNAL(finished()), this, SIGNAL(fadeFinish()));
        connect(fadeAnimation, SIGNAL(finished()), this, SLOT(_fadeAnimationFinished()));
    }
}

CrossFaderWidget::~CrossFaderWidget()
{
    //qDebug("destr");
    this->stopFading();
}

void CrossFaderWidget::takeAndStoreSnapshotsAboutWidgets(QWidget *sourceWidget, QWidget *targetWidget)
{
    // grab a snapshots of the widgets

    // source
    {
        sourceWidgetSnapshot = QPixmap::grabWidget(sourceWidget);

        // Create new picture for transparent
        QPixmap transparent(sourceWidgetSnapshot.size());

        // Do transparency
        transparent.fill(Qt::transparent);
        QPainter p(&transparent);
        p.setCompositionMode(QPainter::CompositionMode_Source);
        p.drawPixmap(0, 0, sourceWidgetSnapshot);
        p.end();

        // Set original picture's reference to new transparent one
        sourceWidgetSnapshot = transparent;
    }

    // target
    {
        targetWidgetSnapshot = QPixmap::grabWidget(targetWidget);

        // Create new picture for transparent
        QPixmap transparent(targetWidgetSnapshot.size());
        //            QPixmap transparent(targetWidget.size());

        // Do transparency
        transparent.fill(Qt::transparent);
        QPainter p(&transparent);
        p.setCompositionMode(QPainter::CompositionMode_Source);
        p.drawPixmap(0, 0, targetWidgetSnapshot);
        p.end();

        // Set original picture's reference to new transparent one
        targetWidgetSnapshot = transparent;
    }
}

void CrossFaderWidget::takeSnapshotsOfWidgetsAndFadeBetweenThem(QWidget *sourceWidget, QWidget *targetWidget,
                                                                QRect sourceSnapshotGeometry, QRect targetSnapshotGeometry,
                                                                int durationMillisec)
{
    this->takeSnapshotsOfWidgetsAndInitializeFading(sourceWidget, targetWidget, sourceSnapshotGeometry, targetSnapshotGeometry);

    // animation
    fadeAnimation->setDuration(durationMillisec);
    fadeAnimation->start();

    guiUpdaterTimer->start();
}

void CrossFaderWidget::takeSnapshotsOfWidgetsAndInitializeFading(QWidget *sourceWidget, QWidget *targetWidget,
                                                                 QRect sourceSnapshotGeometry, QRect targetSnapshotGeometry)
{
    sourceGeom = sourceSnapshotGeometry;
    targetGeom = targetSnapshotGeometry;

    this->takeAndStoreSnapshotsAboutWidgets(sourceWidget, targetWidget);
}

void CrossFaderWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);

#if 1
    painter.setOpacity(1.0f - transitionPercentage);
    painter.drawPixmap(sourceGeom, sourceWidgetSnapshot);

    painter.setOpacity(transitionPercentage);
//    painter.setOpacity(1.0f);
//    qDebug() << "Painter target geom: " << targetGeom;
    painter.drawPixmap(targetGeom, targetWidgetSnapshot);
#endif

    //qDebug() << "paint some nice fading" << this->rect();

    //painter.fillRect(this->rect(), QColor(150 * transitionPercentage, 200 * transitionPercentage, 200 * transitionPercentage));
//    painter.fillRect(targetGeom, QColor(150 * transitionPercentage, 200 * transitionPercentage, 200 * transitionPercentage));
}

void CrossFaderWidget::_fadeAnimationFinished()
{
    guiUpdaterTimer->stop();
    //this->hide();
    //this->deleteLater();

    //qDebug() << "fader size" << this->rect();
}

float CrossFaderWidget::getTransitionPercentage() const
{
    return transitionPercentage;
}

void CrossFaderWidget::setTransitionPercentage(float value)
{
    transitionPercentage = value;
}

void CrossFaderWidget::stopFading()
{
    fadeAnimation->stop();
    this->_fadeAnimationFinished();
}
