#include "frameworkinstaller.h"

#include <QThread>
#include <QMetaClassInfo>

#include "backgroundframeworkinstaller.h"

FrameworkInstaller::FrameworkInstaller(QObject *parent) :
    QObject(parent)
{
    qRegisterMetaType< FrameworkInstallModel >("FrameworkInstallModel");
    qRegisterMetaType< FrameworkInfo >("FrameworkInfo");
}

void FrameworkInstaller::startFrameworkInstallAsync(FrameworkInstallModel frameworkInstallModel)
{
    QThread *fwInstallerBgThread = new QThread;
    BackgroundFrameworkInstaller *fwInstaller = new BackgroundFrameworkInstaller(frameworkInstallModel);

    // connect
    connect(fwInstallerBgThread, SIGNAL(started()), fwInstaller, SLOT(startFrameworkInstall()));

    connect(fwInstaller, SIGNAL(finishedWithSuccess(FrameworkInstallModel)), this, SIGNAL(frameworkInstalled(FrameworkInstallModel)));
    connect(fwInstaller, SIGNAL(finishedWitError(FrameworkInstallModel,QString)), this, SIGNAL(frameworkInstallFailed(FrameworkInstallModel,QString)));

    // destruct
    connect(fwInstaller, SIGNAL(finished()), fwInstallerBgThread, SLOT(quit()));
    connect(fwInstaller, SIGNAL(finished()), this, SLOT(_installFinished()));

    fwInstaller->moveToThread(fwInstallerBgThread);
    fwInstallerBgThread->start();
}

void FrameworkInstaller::_installFinished()
{
    if(this->sender() != NULL) {
        delete this->sender();
    }
}
