#ifndef TESTMASSLOGGERWITHQTHREAD_WORKER_H
#define TESTMASSLOGGERWITHQTHREAD_WORKER_H

#include <QObject>

class TestMassLoggerWithQThread_Worker : public QObject
{
    Q_OBJECT
public:
    explicit TestMassLoggerWithQThread_Worker(QString id, QObject *parent = 0);

public Q_SLOTS:
    void doMassLogging();

Q_SIGNALS:
    void finishedWithItem(QString item);
    void finishedWithWork(QString id);
    void finished();

private:
     QString _id;
};

#endif // TESTMASSLOGGERWITHQTHREAD_WORKER_H
