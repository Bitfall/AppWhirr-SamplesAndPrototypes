#include "frameworkcheckmodel.h"

FrameworkCheckModel::FrameworkCheckModel()
{
}

FrameworkCheckModel::FrameworkCheckModel(FrameworkInfo frameworkInfo, QString frameworkCheckerAppPath, QString frameworkResultFileDirPath) :
    _frameworkInfo(frameworkInfo),
    _frameworkCheckerAppPath(frameworkCheckerAppPath),
    _frameworkResultFileDirPath(frameworkResultFileDirPath)
{
}

FrameworkInfo FrameworkCheckModel::getFrameworkInfo() const
{
    return _frameworkInfo;
}

QString FrameworkCheckModel::getFrameworkCheckerAppPath() const {
    return _frameworkCheckerAppPath;
}

QString FrameworkCheckModel::getFrameworkResultFileDirPath() const
{
    return _frameworkResultFileDirPath;
}
