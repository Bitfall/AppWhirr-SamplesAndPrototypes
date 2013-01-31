//# MagnetManager
//* tarolja MagnetPoint-okat
//* tarolja MagnetWidget-eket
//* fix FPS-en update-el
//* tarolja MagnetLink -eket
//* ! de update stb MagnetPoint-okon megy vegig -> MagnetPoint -hoz tartozik akar tobb MagnetLink, amihez pedig 1 MagnetPoint es 1 MagnetWidget

//## Update
//1) valtozott e valami -> MagnetChangeEvent - ez lehet pl. layout-size change is
//1.a) ha igen akkor MagnetChangeEvent alapjan megvaltoztat MagnetLink-eket
//2) MagnetLink-eken vegigmegy, es ha talal aktivat akkor a link widget-jet a point fele mozgatja


//# MagnetPoint

//# MagnetWidget

//# MagnetLink
//* isActive (befejezodott e)
//*
//


#ifndef MAGNETMANAGER_H
#define MAGNETMANAGER_H

#include <QObject>
#include <QList>

QT_BEGIN_NAMESPACE
class QTimer;
QT_END_NAMESPACE

class MagnetPoint;
class MagnetLink;
class MagnetWidget;
class MagnetEventBase;

class MagnetManager : public QObject
{
    Q_OBJECT
public:
    explicit MagnetManager(QObject *parent = 0);
    explicit MagnetManager(QList<MagnetPoint *> magnetPoints, QList<MagnetWidget *> magnetWidgets, QObject *parent = 0);
private:
    void __commonInit();

//public:
    // do these through events - thread safety
//    void addMagnetPoint(MagnetPoint *magnetPoint);
//    void addMagnetWidget(MagnetWidget *magnetWidget);

private:
    bool event(QEvent *e);

private Q_SLOTS:
    void _doUpdate();

    void _magnetPointPositionChanged(MagnetPoint *source);

private:
    void _wakeMagnetManager();
    void __sleepMagnetManager();


private:
    QList<MagnetWidget *> _magnetWidgets;
    QList<MagnetPoint *> _magnetPoints;
    QList<MagnetEventBase *> _unprocessedMagnetEvents;

    QTimer *_updaterTimer;
};

#endif // MAGNETMANAGER_H
