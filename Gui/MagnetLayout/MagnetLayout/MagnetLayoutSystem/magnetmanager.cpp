#include "magnetmanager.h"

#include <QTimer>
#include <QEvent>

// magnet
#include "magnetpoint.h"
#include "magnetwidget.h"
#include "magnetlink.h"
// magnet events
#include "Events/magnetpointaddedevent.h"

// config
#define MAGNET_SYSTEM_UPDATE_INTERVAL_MILLISECONDS  34 // ~30 FPS

MagnetManager::MagnetManager(QObject *parent) :
    QObject(parent)
{
    this->__commonInit();
}

MagnetManager::MagnetManager(QList<MagnetPoint *> magnetPoints, QList<MagnetWidget *> magnetWidgets, QObject *parent) :
    QObject(parent)
{
    this->_magnetPoints = magnetPoints;
    this->_magnetWidgets = magnetWidgets;

    _unprocessedMagnetEvents.append(new MagnetPointAddedEvent());

    this->__commonInit();
}

void MagnetManager::__commonInit()
{
    _updaterTimer = new QTimer(this);
    _updaterTimer->setInterval(MAGNET_SYSTEM_UPDATE_INTERVAL_MILLISECONDS);
    connect(_updaterTimer, SIGNAL(timeout()), this, SLOT(_doUpdate()));
}

void MagnetManager::_doUpdate()
{
    for(int i = 0; i < _unprocessedMagnetEvents.size(); ++i) {
        MagnetEventBase *currEvent = _unprocessedMagnetEvents[i];

        if(currEvent->type() == MagnetPointAddedEvent::getCustomEventType()) {
            DLog("Magnet point added.");
        }

        delete currEvent;
    }
    _unprocessedMagnetEvents.clear();

    this->__sleepMagnetManager();
}

void MagnetManager::_magnetPointPositionChanged(MagnetPoint *source) {


}

bool MagnetManager::event(QEvent *e) {

    return QObject::event(e);
}

//void MagnetManager::addMagnetPoint(MagnetPoint *magnetPoint) {
//    magnetPoint->setParent(this);
//    _magnetPoints.append(magnetPoint);
//    connect(magnetPoint, SIGNAL(positionChanged(MagnetPoint*)), this, SLOT(_magnetPointPositionChanged(MagnetPoint*)));
//    this->_wakeMagnetManager();
//}

//void MagnetManager::addMagnetWidget(MagnetWidget *magnetWidget) {
//    magnetWidget->setParent(this);
//    _magnetWidgets.append(magnetWidget);
//    this->_wakeMagnetManager();
//}



void MagnetManager::_wakeMagnetManager() {
    if(!_updaterTimer->isActive()) {
        _updaterTimer->start();
    }
}

void MagnetManager::__sleepMagnetManager() {
    _updaterTimer->stop();
}
