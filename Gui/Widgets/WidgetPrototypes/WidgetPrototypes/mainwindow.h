#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class IntelligentSeparatedMultifunctionalButtonWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void defaultOptionActivated();
    void optionOneActivated();
    void optionTwoActivated();
    void optionThreeActivated();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;

    IntelligentSeparatedMultifunctionalButtonWidget *intelligentTestButton;
};

#endif // MAINWINDOW_H
