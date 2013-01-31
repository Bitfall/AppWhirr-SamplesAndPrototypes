#ifndef MAGNETEVENTBASE_H
#define MAGNETEVENTBASE_H

#include <QEvent>

class MagnetEventBase : public QEvent {
public:
    MagnetEventBase(Type type) : QEvent(type) {}
    ~MagnetEventBase() {}
};

#endif // MAGNETEVENTBASE_H
