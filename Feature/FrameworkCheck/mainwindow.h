#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>

QT_BEGIN_NAMESPACE
class QPushButton;
class QLineEdit;
QT_END_NAMESPACE


#include "Common/Framework/frameworkcheckmodel.h"
#include "Common/Framework/frameworkinstallmodel.h"

class CustomAppInstallManager;

class SupportedFrameworkInfos;
class AvailableFrameworkChecker;
class FrameworkInstaller;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private Q_SLOTS:
    void _installRequiredFrameworks();
    void _checkForFrameworks();

    void _installTheseFrameworks(QList<FrameworkCheckModel> frameworkCheckInfos);
    void _availableFrameworksFound(QList<FrameworkCheckModel> frameworkCheckInfos);
    void _frameworkCheckingFinished();

    // --- install
    void _frameworkInstalled(FrameworkInstallModel frameworkInstallModel);
    void _frameworkInstallFailed(FrameworkInstallModel frameworkInstallModel, QString errorMessage);

private:
    QPushButton *_installFrameworksButton;
    QPushButton *_checkForFrameworksButton;
    QLineEdit *_requiredFrameworksLineEdit;

    SupportedFrameworkInfos *_supportedFrameworkInfos;
    AvailableFrameworkChecker *_frameworkChecker;
    FrameworkInstaller *_frameworkInstaller;

    QMap<quint32, QString> _frameworkIdToFrameworkInstallerPathMap;
};

#endif // MAINWINDOW_H
