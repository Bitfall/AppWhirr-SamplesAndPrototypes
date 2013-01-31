#ifndef MAGNETPOINTADDEDEVENT_H
#define MAGNETPOINTADDEDEVENT_H

#include <QEvent>

#include "magneteventbase.h"

class MagnetPointAddedEvent : public MagnetEventBase
{
public:
    static inline Type getCustomEventType()
    {
        static Type sEventType = static_cast<QEvent::Type>(QEvent::registerEventType());
        return sEventType;
    }

    explicit MagnetPointAddedEvent();
};

#endif // MAGNETPOINTADDEDEVENT_H
