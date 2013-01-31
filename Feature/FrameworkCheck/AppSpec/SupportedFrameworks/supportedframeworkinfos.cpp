#include "supportedframeworkinfos.h"

SupportedFrameworkInfos::SupportedFrameworkInfos(QObject *parent) :
    QObject(parent)
{
    // MSVC 2005 redist
    _supportedFrameworks.append(FrameworkInfo(SFI_MSVC2005redist_x86, "MSVC 2005 redist (x86)"));
    _frameworkIdToFrameworkCheckerMap.insert(SFI_MSVC2005redist_x86, "./frameworks/checkers/msvc2005redist_checker.exe");
    _supportedFrameworks.append(FrameworkInfo(SFI_MSVC2005redist_x64, "MSVC 2005 redist (x64)"));
    _frameworkIdToFrameworkCheckerMap.insert(SFI_MSVC2005redist_x64, "./frameworks/checkers/msvc2005redist_checker.exe");

    // MSVC 2008 redist
    _supportedFrameworks.append(FrameworkInfo(SFI_MSVC2008redist_x86, "MSVC 2008 redist (x86)"));
    _frameworkIdToFrameworkCheckerMap.insert(SFI_MSVC2008redist_x86, "./frameworks/checkers/msvc2008redist_checker.exe");
    _supportedFrameworks.append(FrameworkInfo(SFI_MSVC2008redist_x64, "MSVC 2008 redist (x64)"));
    _frameworkIdToFrameworkCheckerMap.insert(SFI_MSVC2008redist_x64, "./frameworks/checkers/msvc2008redist_checker.exe");

    // dotNet 3
    _supportedFrameworks.append(FrameworkInfo(SFI_DotNet30, ".Net 3.0"));
    _frameworkIdToFrameworkCheckerMap.insert(SFI_DotNet30, "./frameworks/checkers/DotNet30_FwChecker.exe");

    // dotNet 4
    _supportedFrameworks.append(FrameworkInfo(SFI_DotNet40, ".Net 4.0"));
    _frameworkIdToFrameworkCheckerMap.insert(SFI_DotNet40, "./frameworks/checkers/DotNet40_FwChecker.exe");
}

QList<FrameworkInfo> SupportedFrameworkInfos::getSupportedFrameworks() const
{
    return _supportedFrameworks;
}

QString SupportedFrameworkInfos::getFrameworkCheckerPathForFramework(quint32 frameworkId) const
{
    return _frameworkIdToFrameworkCheckerMap.value(frameworkId, QString());
}
