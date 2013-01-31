#include <QtGui/QApplication>
#include "mainwindow.h"

#ifndef UNIT_TEST_ENABLED

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}

#else

#include "UnitTests/testexample.h"
#include "UnitTests/testclass1unittest.h"

int main(int argc, char *argv[])
{
    TestExample test1;
    QTest::qExec(&test1, argc, argv);

    TestClass1UnitTest testClass1UnitTest;
    QTest::qExec(&testClass1UnitTest, argc, argv);

    return 0;
}

#endif
