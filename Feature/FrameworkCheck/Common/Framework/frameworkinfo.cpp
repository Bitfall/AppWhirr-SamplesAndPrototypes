#include "frameworkinfo.h"

FrameworkInfo::FrameworkInfo() :
    _frameworkId(0)
{
}

FrameworkInfo::FrameworkInfo(quint32 frameworkId, QString frameworkPrintableName) :
    _frameworkId(frameworkId),
    _frameworkPrintableName(frameworkPrintableName)
{
}

quint32 FrameworkInfo::getFrameworkId() const
{
    return _frameworkId;
}

QString FrameworkInfo::getFrameworkPrintableName() const
{
    return _frameworkPrintableName;
}
