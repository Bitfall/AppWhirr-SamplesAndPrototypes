#ifndef VIDEOINWEBVIEWWINDOW_H
#define VIDEOINWEBVIEWWINDOW_H

#include <QMainWindow>

namespace Ui {
    class VideoInWebviewWindow;
}

class VideoInWebviewWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit VideoInWebviewWindow(QWidget *parent = 0);
    ~VideoInWebviewWindow();

private slots:
    void on_pushButton_clicked();

private:
    Ui::VideoInWebviewWindow *ui;
};

#endif // VIDEOINWEBVIEWWINDOW_H
