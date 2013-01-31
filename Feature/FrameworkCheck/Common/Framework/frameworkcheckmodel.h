#ifndef FRAMEWORKCHECKMODEL_H
#define FRAMEWORKCHECKMODEL_H

#include <QString>

#include "../Framework/frameworkinfo.h"

class FrameworkCheckModel
{
public:
    /*! Default constructor - required by Qt meta object system
    */
    explicit FrameworkCheckModel();

    /*! Constructor

        @param frameworkId : internal Id of the framework
        @param frameworkName : the presentable frameworkName
        @param frameworkCheckerAppPath : path for the checker app
        @param frameworkResultFileDirPath : path of the \b directory will contain the result-file
    */
    explicit FrameworkCheckModel(FrameworkInfo frameworkInfo, QString frameworkCheckerAppPath, QString frameworkResultFileDirPath);

    FrameworkInfo getFrameworkInfo() const;
    QString getFrameworkCheckerAppPath() const;
    QString getFrameworkResultFileDirPath() const;

private:
    FrameworkInfo _frameworkInfo;
    QString _frameworkCheckerAppPath;
    QString _frameworkResultFileDirPath;
};

#endif // FRAMEWORKCHECKMODEL_H
