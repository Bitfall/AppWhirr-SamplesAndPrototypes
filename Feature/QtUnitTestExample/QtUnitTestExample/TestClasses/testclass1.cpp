#include "testclass1.h"

TestClass1::TestClass1(QObject *parent) :
    QObject(parent)
{
}

QString TestClass1::returnHello()
{
    return QString("Hello");
}

QString TestClass1::returnWorld()
{
    return QString("World");
}
