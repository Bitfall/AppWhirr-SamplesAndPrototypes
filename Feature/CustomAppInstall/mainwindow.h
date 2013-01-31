#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

QT_BEGIN_NAMESPACE
class QPushButton;
class QTextEdit;
class QLineEdit;
QT_END_NAMESPACE

class CustomAppInstallManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void startTest();

    void _customAppInstallFinishedWithSuccess();
    void _customAppInstallFinishedWithError(QString errorMessage);
private:
    QPushButton *_doTestButton;
    QLineEdit *_installFilePathLineEdit;
    QTextEdit *_logTextEdit;

    CustomAppInstallManager *_customAppInstallManager;
};

#endif // MAINWINDOW_H
