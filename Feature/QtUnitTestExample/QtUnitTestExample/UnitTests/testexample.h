#ifndef TESTEXAMPLE_H
#define TESTEXAMPLE_H

#include <QObject>
#include <QtTest/QtTest>

class TestExample : public QObject
{
    Q_OBJECT
public:
    explicit TestExample(QObject *parent = 0);

private slots:
    void toUpper();
    void thisWillGenerateFail();
    void testBenchmark();
    void abortTestingIfItFails();
};

#endif // TESTEXAMPLE_H
