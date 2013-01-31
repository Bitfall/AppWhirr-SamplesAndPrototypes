#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

class MultiContentManager;
class ReferenceCountingIdBasedCollection;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void _switchToContentOne();
    void _switchToContentTwo();

    void _addContentToContentTwo();
    void _removeContentTwo();

private:
    MultiContentManager *_multiContentManager;
    ReferenceCountingIdBasedCollection *_contentItemCollection;
};

#endif // MAINWINDOW_H
