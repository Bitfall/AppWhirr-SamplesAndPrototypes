#ifndef TESTCLASS1_H
#define TESTCLASS1_H

#include <QObject>
#include <QString>

class TestClass1 : public QObject
{
    Q_OBJECT
public:
    explicit TestClass1(QObject *parent = 0);

    QString returnHello();
    QString returnWorld();

};

#endif // TESTCLASS1_H
