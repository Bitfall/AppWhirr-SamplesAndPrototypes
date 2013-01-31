#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

#include "Common/idbasediteminterface.h"
#include "Common/referencecountingidbasedcollection.h"

QT_BEGIN_NAMESPACE
class QPushButton;
class QElapsedTimer;
QT_END_NAMESPACE



class TestItem : public IdBasedItemInterface
{
public:
    explicit TestItem(QString itemId) : _itemId(itemId) {}
    QString getId() const { return _itemId; }

private:
    QString _itemId;
};

class RefTester : public QObject
{
    Q_OBJECT
public:
    explicit RefTester(QString testId, ReferenceCountingIdBasedCollection *refCountingCollection, bool isRetain, QObject *parent=0) : QObject(parent), _testId(testId), _refCountingCollection(refCountingCollection), _isRetain(isRetain) {}

public Q_SLOTS:
    void startTesting()
    {
        for(int iter = 0; iter < 100; ++iter) {
            for(int i = 0; i < 10; ++i) {
                if(_isRetain) {
                    _refCountingCollection->retainItem(QString::number(i));
                } else {
                    _refCountingCollection->releaseItem(QString::number(i));
                }
            }
        }

        Q_EMIT finishedWithTesting();
        Q_EMIT finishedWithTesting_Id(this->_testId);
    }

Q_SIGNALS:
    void finishedWithTesting();
    void finishedWithTesting_Id(QString testId);

private:
    QString _testId;
    ReferenceCountingIdBasedCollection *_refCountingCollection;
    bool _isRetain;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void _startTesting();
    void _testFinished(QString testId);

private:
    ReferenceCountingIdBasedCollection *_testCollection;
    int _testerCount;

    QPushButton *_doTestButton;

    QElapsedTimer *_elapsedTimer;
};

#endif // MAINWINDOW_H
