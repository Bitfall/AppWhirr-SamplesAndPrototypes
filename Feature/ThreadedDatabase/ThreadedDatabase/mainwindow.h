#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void doMagicButtonPressed();
    void _serverStartedStartMagic();
    void _serverShutDown();

    void finishedWithWork(QString threadId);
    void itemFinished(QString item);

    void resultFor_getFromPeopleByAge(QString name,int age,QString notes,bool isSuccess);

private:
    void finishedWithAddingItems();

private:
    QStringList _testWorkIds;
};

#endif // MAINWINDOW_H
