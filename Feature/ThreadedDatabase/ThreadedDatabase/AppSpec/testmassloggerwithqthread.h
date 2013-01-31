#ifndef TESTMASSLOGGERWITHQTHREAD_H
#define TESTMASSLOGGERWITHQTHREAD_H

#include <QThread>

#include "testmassloggerwithqthread_worker.h"

class TestMassLoggerWithQThread : public QThread
{
    Q_OBJECT
public:
    explicit TestMassLoggerWithQThread(QObject *parent = 0);

    void startWorker();

Q_SIGNALS:
    void finishedWithItem(QString item);
    void finished(QString id);

protected:
    void run();

private Q_SLOTS:
    void finishedSlot(QString id);

private:
     TestMassLoggerWithQThread_Worker *_worker;
};

#endif // TESTMASSLOGGERWITHQTHREAD_H
