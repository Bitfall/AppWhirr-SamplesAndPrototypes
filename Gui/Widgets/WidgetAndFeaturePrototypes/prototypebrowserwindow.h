#ifndef PROTOTYPEBROWSERWINDOW_H
#define PROTOTYPEBROWSERWINDOW_H

#include <QtGui/QMainWindow>

class PrototypeBrowserWindow : public QMainWindow
{
    Q_OBJECT

public:
    PrototypeBrowserWindow(QWidget *parent = 0);

private Q_SLOTS:
    void presentMenuPrototype1();
    void presentVideoInWebviewButton();
};

#endif // PROTOTYPEBROWSERWINDOW_H
