#include "testexample.h"

TestExample::TestExample(QObject *parent) :
    QObject(parent)
{
}

void TestExample::toUpper()
{
    QString str = "Hello";
    QCOMPARE(str.toUpper(), QString("HELLO"));
}

void TestExample::thisWillGenerateFail()
{
    QCOMPARE(QString("One"), QString("Two"));
}

void TestExample::testBenchmark()
{
    QString str1 = QLatin1String("This is a test string");
    QString str2 = QLatin1String("This is a test string");
    QBENCHMARK {
        int sum = 0;
        for(int i = 0; i < 10000; i++) {
            sum += i;
        }

        str1.localeAwareCompare(str2);
    }
}

void TestExample::abortTestingIfItFails()
{
    QEXPECT_FAIL("data27", "Oh my, this is soooo broken", Abort);
    QCOMPARE(43, 42);

    // or an Assert like version:
    QFAIL("This test has not been ported to this platform yet.");

    // this is the same as compare but it will Assert as well
//    QTEST(QString("One"), QString("Thow"));
}
