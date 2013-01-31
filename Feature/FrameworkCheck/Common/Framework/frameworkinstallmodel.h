#ifndef FRAMEWORKINSTALLMODEL_H
#define FRAMEWORKINSTALLMODEL_H

#include "frameworkinfo.h"

class FrameworkInstallModel
{
public:
    /*! Default constructor - required by Qt meta info system
    */
    explicit FrameworkInstallModel();
    explicit FrameworkInstallModel(FrameworkInfo frameworkInfo, QString frameworkInstallerPath);

    FrameworkInfo getFrameworkInfo() const;
    QString getFrameworkInstallerPath() const;

private:
    FrameworkInfo _frameworkInfo;
    QString _frameworkInstallerPath;
};

#endif // FRAMEWORKINSTALLMODEL_H
