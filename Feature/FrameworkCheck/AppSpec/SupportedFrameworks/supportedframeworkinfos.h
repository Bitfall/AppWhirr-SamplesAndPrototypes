#ifndef SUPPORTEDFRAMEWORKINFOS_H
#define SUPPORTEDFRAMEWORKINFOS_H

#include <QObject>
#include <QMap>

#include "Common/Framework/frameworkinfo.h"

class SupportedFrameworkInfos : public QObject
{
    Q_OBJECT

public:
    enum SupportedFrameworkIdsEnum {
        SFI_MSVC2005redist_x86 = 1,
        SFI_MSVC2005redist_x64 = 2,
        SFI_MSVC2008redist_x86 = 3,
        SFI_MSVC2008redist_x64 = 4,

        SFI_DotNet30 = 5,
        SFI_DotNet40 = 6
    };

public:
    explicit SupportedFrameworkInfos(QObject *parent = 0);
    
    QList<FrameworkInfo> getSupportedFrameworks() const;

    /*!

        @return The framework-checker app path related to the given \a frameworkId , or an empty string if the Id is not found.
    */
    QString getFrameworkCheckerPathForFramework(quint32 frameworkId) const;

private:
    QList<FrameworkInfo> _supportedFrameworks;
    QMap<quint32, QString> _frameworkIdToFrameworkCheckerMap;
};

#endif // SUPPORTEDFRAMEWORKINFOS_H
