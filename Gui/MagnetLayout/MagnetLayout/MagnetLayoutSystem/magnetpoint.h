#ifndef MAGNETPOINT_H
#define MAGNETPOINT_H

#include <QWidget>
#include <QPointF>

class MagnetPoint : public QWidget
{
    Q_OBJECT
public:
    explicit MagnetPoint(QWidget *parent = 0);

    QPointF getPosition() const;

Q_SIGNALS:
    void positionChanged(MagnetPoint *source);

protected:
    void resizeEvent(QResizeEvent *e);
};

#endif // MAGNETPOINT_H
