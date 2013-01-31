#ifndef HELLO_H
#define HELLO_H

#include <QObject>

class Hello : public QObject {
Q_OBJECT
signals:
    void done();
public slots:
    void world();
};

#endif // HELLO_H
