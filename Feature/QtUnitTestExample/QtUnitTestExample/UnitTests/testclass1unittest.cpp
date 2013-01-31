#include "testclass1unittest.h"

#include "TestClasses/testclass1.h"

TestClass1UnitTest::TestClass1UnitTest(QObject *parent) :
    QObject(parent)
{
}

void TestClass1UnitTest::testReturnHelloMethod()
{
    TestClass1 *testClass = new TestClass1();
    QString str = "Hello";
    QCOMPARE(str, testClass->returnHello());

    delete testClass;
}

void TestClass1UnitTest::testReturnWorldMethod()
{
    TestClass1 *testClass = new TestClass1();
    QString str = "World";
    QCOMPARE(str, testClass->returnWorld());

    delete testClass;
}

void TestClass1UnitTest::testWholeTestClass1()
{
    this->testReturnHelloMethod();
    this->testReturnWorldMethod();
}
