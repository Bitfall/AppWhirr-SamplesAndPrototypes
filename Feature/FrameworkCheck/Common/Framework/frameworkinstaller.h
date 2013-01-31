#ifndef FRAMEWORKINSTALLER_H
#define FRAMEWORKINSTALLER_H

#include <QObject>

#include "frameworkinstallmodel.h"

class FrameworkInstaller : public QObject
{
    Q_OBJECT
public:
    explicit FrameworkInstaller(QObject *parent = 0);

    void startFrameworkInstallAsync(FrameworkInstallModel frameworkInstallModel);

Q_SIGNALS:
    void frameworkInstalled(FrameworkInstallModel frameworkInstallModel);
    void frameworkInstallFailed(FrameworkInstallModel frameworkInstallModel, QString errorMessage);

private Q_SLOTS:
    void _installFinished();
};

#endif // FRAMEWORKINSTALLER_H
