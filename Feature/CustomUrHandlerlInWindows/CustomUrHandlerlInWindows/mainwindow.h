#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

QT_BEGIN_NAMESPACE
class QLabel;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QString initialStatusMessage, QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void registerUrlSchemeButtonPressed();

private:
#ifdef Q_WS_WIN
    // the given urlSchemePrefix is -> if you want to register a scheme like this: 'testscheme://the-url-part' then give the urlSchemePrefix 'testscheme'
    bool win_RegisterCustomUrlScheme(QString urlSchemePrefix, QString targetAppPathToCall, QString iconPath);
#endif

private:
    QLabel *_statusLabel;
};

#endif // MAINWINDOW_H
