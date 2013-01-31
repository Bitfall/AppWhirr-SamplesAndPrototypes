#ifndef TESTCLASS1UNITTEST_H
#define TESTCLASS1UNITTEST_H

#include <QObject>
#include <QtTest/QtTest>

class TestClass1UnitTest : public QObject
{
    Q_OBJECT
public:
    explicit TestClass1UnitTest(QObject *parent = 0);

private slots:
    void testReturnHelloMethod();
    void testReturnWorldMethod();

    void testWholeTestClass1();
};

#endif // TESTCLASS1UNITTEST_H
