#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

QT_BEGIN_NAMESPACE
class QEvent;
class QScrollArea;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    bool eventFilter(QObject* object, QEvent* event);

private:
    void processMouseButtonPressEvent(QObject *obj, QMouseEvent *e);
    void processMouseMoveEvent(QObject *obj, QMouseEvent *e);
    void processMouseButtonReleaseEvent(QObject *obj, QMouseEvent *e);

private:
    QPoint mouseScrollStartPos;
    QPoint scrollOffset;
    QScrollArea *scrollArea;
};

#endif // MAINWINDOW_H
