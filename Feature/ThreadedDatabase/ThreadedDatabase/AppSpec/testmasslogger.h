#ifndef TESTMASSLOGGER_H
#define TESTMASSLOGGER_H

#include <QObject>
#include <QRunnable>

class TestMassLogger : public QObject, public QRunnable
{
    Q_OBJECT
public:
    TestMassLogger(QString testId);

Q_SIGNALS:
    void finishedWithItem(QString item);
    void finished(QString id);

protected:
    void run();

private:
    QString _testId;
};

#endif // TESTMASSLOGGER_H
