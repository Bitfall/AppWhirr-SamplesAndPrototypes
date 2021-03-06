#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

QT_BEGIN_NAMESPACE
class QLineEdit;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void _startCopyTest();
    void _startDeleteTest();

private:
    QLineEdit *_testSrcDirLineEdit;
    QLineEdit *_testDestDirLineEdit;
};

#endif // MAINWINDOW_H
