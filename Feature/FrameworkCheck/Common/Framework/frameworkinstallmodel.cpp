#include "frameworkinstallmodel.h"

FrameworkInstallModel::FrameworkInstallModel()
{
}

FrameworkInstallModel::FrameworkInstallModel(FrameworkInfo frameworkInfo, QString frameworkInstallerPath) :
    _frameworkInfo(frameworkInfo),
    _frameworkInstallerPath(frameworkInstallerPath)
{
}

FrameworkInfo FrameworkInstallModel::getFrameworkInfo() const
{
    return _frameworkInfo;
}

QString FrameworkInstallModel::getFrameworkInstallerPath() const
{
    return _frameworkInstallerPath;
}
