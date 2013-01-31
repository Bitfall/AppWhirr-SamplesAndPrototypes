#include "pathhelper.h"

#include <QDir>
#include <QFile>
//#include <QSettings>
#include <QProcess>

//#include "../EasyAppsClient/Common/Helpers/qstringhelper.h"

// debug and utility
//#include "../Database/simplelogdatabasemanager.h"

//#define PATH_MANAGER_INTERNAL_LOG_TO_DATABASE(logMessage) SimpleLogDatabaseManager::writeToLog("Internal_PathHelper.db", logMessage);

#ifdef Q_WS_MAC
#include <Carbon/Carbon.h>
#include <ApplicationServices/ApplicationServices.h>
//#include "../Application/macprocess.h"
//#include "qstringhelper.h"
#endif

#ifdef Q_WS_WIN
#include <windows.h>
#include <Shlobj.h>
#pragma comment(lib,"user32.lib")
#pragma comment(lib,"shell32.lib")

//#include "../Application/win_applicationprocessbyexedata.h"
//#include "../Application/platformspecificprogramidentifierhelper.h"
#endif

PathHelper::PathHelper()
{
}

// -----------------------------------------------
// --- system specific directories and pathers ---

QString PathHelper::getLocalDesktopPath()
{
    //
    // !!! QDesktopServices::storageLocation could be used for this as well
    //

    QString localDesktopPath = "";

#ifdef Q_WS_WIN
    // SHGetFolderPathW: (http://msdn.microsoft.com/en-us/library/bb762181(v=vs.85).aspx)
    // minimum windows version: 2000, XP
    WCHAR szPath[MAX_PATH];
    if(SUCCEEDED(SHGetFolderPathW(NULL,
                                 CSIDL_DESKTOP|CSIDL_FLAG_CREATE,
                                 NULL,
                                 0,
                                 szPath)))
    {
        localDesktopPath = QString::fromWCharArray(szPath);
    }

    // SHGetKnownFolderPath: "This function replaces SHGetFolderPath. That older function is now simply a wrapper for SHGetKnownFolderPath."
    // from Windows Vista the desired way is: SHGetKnownFolderPath (http://msdn.microsoft.com/en-us/library/bb762188(v=vs.85).aspx)
    //  BUT SHGetKnownFolderPath requires Vista as minimum OS !!
#endif

#ifdef Q_WS_MAC
    localDesktopPath = "~/Desktop";
#endif

    return localDesktopPath;
}

#ifdef Q_WS_WIN

QString PathHelper::getWinSpecStartMenuPath()
{
    QString startupProgramsFolderPath; // empty QString

    // SHGetFolderPathW: (http://msdn.microsoft.com/en-us/library/bb762181(v=vs.85).aspx)
    // minimum windows version: 2000, XP
    WCHAR szPath[MAX_PATH];
    if(SUCCEEDED(SHGetFolderPathW(NULL,
                                 CSIDL_STARTMENU|CSIDL_FLAG_CREATE,
                                 NULL,
                                 0,
                                 szPath)))
    {
        startupProgramsFolderPath = QString::fromWCharArray(szPath);
    }

    // SHGetKnownFolderPath: "This function replaces SHGetFolderPath. That older function is now simply a wrapper for SHGetKnownFolderPath."
    // from Windows Vista the desired way is: SHGetKnownFolderPath (http://msdn.microsoft.com/en-us/library/bb762188(v=vs.85).aspx)
    //  BUT SHGetKnownFolderPath requires Vista as minimum OS !!

    return startupProgramsFolderPath;
}

QString PathHelper::getWinSpecProgramFilesPath()
{
    QString win_programFilesPath; // empty QString

    // SHGetFolderPathW: (http://msdn.microsoft.com/en-us/library/bb762181(v=vs.85).aspx)
    // minimum windows version: 2000, XP
    WCHAR szPath[MAX_PATH];
    if(SUCCEEDED(SHGetFolderPathW(NULL,
                                 CSIDL_PROGRAM_FILES,
                                 NULL,
                                 0,
                                 szPath)))
    {
        win_programFilesPath = QString::fromWCharArray(szPath);
    }

    // SHGetKnownFolderPath: "This function replaces SHGetFolderPath. That older function is now simply a wrapper for SHGetKnownFolderPath."
    // from Windows Vista the desired way is: SHGetKnownFolderPath (http://msdn.microsoft.com/en-us/library/bb762188(v=vs.85).aspx)
    //  BUT SHGetKnownFolderPath requires Vista as minimum OS !!

    return win_programFilesPath;
}

QString PathHelper::getWinSpecStartupPath()
{
    QString startupProgramsFolderPath; // empty QString

    // SHGetFolderPathW: (http://msdn.microsoft.com/en-us/library/bb762181(v=vs.85).aspx)
    // minimum windows version: 2000, XP
    WCHAR szPath[MAX_PATH];
    if(SUCCEEDED(SHGetFolderPathW(NULL,
                                 CSIDL_STARTUP|CSIDL_FLAG_CREATE,
                                 NULL,
                                 0,
                                 szPath)))
    {
        startupProgramsFolderPath = QString::fromWCharArray(szPath);
    }

    // SHGetKnownFolderPath: "This function replaces SHGetFolderPath. That older function is now simply a wrapper for SHGetKnownFolderPath."
    // from Windows Vista the desired way is: SHGetKnownFolderPath (http://msdn.microsoft.com/en-us/library/bb762188(v=vs.85).aspx)
    //  BUT SHGetKnownFolderPath requires Vista as minimum OS !!

    return startupProgramsFolderPath;
}

#endif


// -----------------------------------------------------------------
// --- utility functions to easy the work with Qt dirs and files ---

bool PathHelper::deleteThisDirectoryAndEverythingBelow(QString topDirPath)
{
    DLog("-- deleteThisDirectoryAndEverythingBelow: ") << topDirPath;

    {
        QDir topDir(topDirPath);

        if (!topDir.exists()) {
            WLog(QString("The given topDir does not exists: %1").arg(topDirPath));
            return true;
        }

        //First delete any files in the current directory + symlinks to anything except directories
        QFileInfoList files = topDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files | QDir::Hidden | QDir::System | QDir::Drives/* | QDir::NoSymLinks*/);
        for(int i = 0; i < files.count(); i++)
        {
            QString currFileInPath = files.at(i).fileName();
            QString currFileFullPath = topDir.filePath(currFileInPath);
            QFileInfo currFileInfo(currFileFullPath);
            if( !currFileInfo.isSymLink() && !currFileInfo.isFile() ) {
                WLog("Not a symlink and not a file! Cannot remove it!") << currFileFullPath;
                return false;
            }

            if( !topDir.remove(currFileInPath) )
            {
                WLog(QString("The specified file cannot be removed: %1 | full path: %2").arg(currFileInPath).arg(files.at(i).absoluteFilePath()));
                return false;
            }
        }

        // Now recursively delete any child directories
        QFileInfoList dirs = topDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Hidden);
        for(int i = 0; i < dirs.count(); i++)
        {
            QString currDirAbsolutePath = dirs.at(i).absoluteFilePath();
            if(QFileInfo(currDirAbsolutePath).isSymLink()) {
                // it's a symlink to a dir, simply remove this symlink file
                DLog(QString("The dir is a symlink file [%1]. Simply remove it.").arg(currDirAbsolutePath));
                if(!QDir().remove(currDirAbsolutePath))
                {
                        WLog("Failed to remove the symlink file: " << currDirAbsolutePath);
                        return false;
                }
            }
            else if( !PathHelper::deleteThisDirectoryAndEverythingBelow( currDirAbsolutePath ) ) {
                WLog("Failed to delete subdir: ") << currDirAbsolutePath;
                return false;
            }
        }
    }

    //Finally, remove empty top directory
    if( !QDir().rmdir(topDirPath) )
    {
        WLog(QString("The specified directory cannot be removed: %1. Maybe it's still not empty.").arg(topDirPath));
        return false;
    }

    return true;
}

bool PathHelper::copyWholeDirectory(QString sourceDirPath, QString destDirPath, bool isCopyOnlyContentOfSource, SymlinkHandlingModeEnum symlinkHandlingMode, bool isFailWhenContentCopyFails)
{
    if(!isCopyOnlyContentOfSource) {
        // copy the folder as well
        QDir sourceDir(sourceDirPath);
        QString newDestDirPath = PathHelper::combineAndCleanPathes(destDirPath, sourceDir.dirName());
        return PathHelper::copyWholeDirectory_recursive(sourceDirPath, newDestDirPath, symlinkHandlingMode, isFailWhenContentCopyFails);
    }

    // copy only the sub dirs
    QDir sourceDir(sourceDirPath);
    if(!sourceDir.exists()) {
        WLogS << " ! The specified source path does not exists: " << sourceDirPath;
        return false;
    }

    QStringList subDirs = sourceDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden/*| QDir::NoSymLinks*/);
    if(subDirs.isEmpty()) {
#ifdef ENABLE_PATH_MANAGER_LOGGING
        DLogS << "The specified source directory is empty.";
#endif
        return true;
    }

    for(int i = 0; i < subDirs.count(); i++)
    {
        QString srcDirFullPath = PathHelper::combineAndCleanPathes(sourceDirPath, subDirs[i]);
        QString destDirFullPath = PathHelper::combineAndCleanPathes(destDirPath, subDirs[i]);
        QFileInfo srcFInfo(srcDirFullPath);

        if(PathHelper::isSymlink(srcDirFullPath)) {
            DLog(QString(" - (Dir)Symlink %1 found for target %2").arg(srcDirFullPath).arg(srcFInfo.symLinkTarget()));

            if(symlinkHandlingMode == SHM_UseAsFile) {
                // use as file

#ifdef Q_OS_WIN
                // copy it as a normal file
                if(!QFile::copy(srcDirFullPath, destDirFullPath)) {
                    WLog(QString(" ! Cannot copy the symlink-file from [%1] to [%2]").arg(srcDirFullPath).arg(destDirFullPath));
                    return false;
                }
#endif

#ifdef Q_OS_MAC
//                if(QFileInfo(srcDirFullPath).symLinkTarget().isEmpty()) {
//                    WLog("Symlink found, but target is empty: ") << srcDirFullPath;
//                    continue;
//                }

                /////
                //QDir sourceDir(sourceDirPath);
                QString symlinkPath = getSymlinkTarget(QFileInfo(srcDirFullPath).absoluteFilePath());
                //sourceDir.relativeFilePath(srcFInfo.symLinkTarget());

                DLog(QString("Symlink created at path %1 with target %2").arg(destDirFullPath).arg(symlinkPath));

                /////

                if( !QFile::link(symlinkPath, destDirFullPath) ) {
                    WLog("Symlink cannot be created!");
                    if(isFailWhenContentCopyFails) {
                        WLog(" - Fail");
                        return false;
                    }
                }
#endif
            }
            else if(symlinkHandlingMode == SHM_UseAsTarget) {
                WLog("!!!!!!!! Not yet implemented! (will be ignored)");
            }
            else {
                DLog("Symlink handling mode: ignore.");
            }
        }
        else {
            QString destName = PathHelper::combineAndCleanPathes(destDirPath, subDirs[i]);
            if(!PathHelper::copyWholeDirectory_recursive(srcDirFullPath, destName, symlinkHandlingMode, isFailWhenContentCopyFails)) {
                return false;
            }
        }
    }

    // also copy the files from sourceDirPath
    if(!PathHelper::copyOnlyFilesOfDirectory(sourceDirPath, destDirPath, symlinkHandlingMode, true)) {
        if(isFailWhenContentCopyFails) {
            return false;
        }
    }

    return true;
}

bool PathHelper::copyOnlyFilesOfDirectory(QString sourceDirPath, QString destDirPath, SymlinkHandlingModeEnum symlinkHandlingMode, bool isIgnoreDirectorySymlinks)
{
//    FLAG_FOR_REVIEW_WITH_HINT("Should copy symlink / shortcut files as well?? Temporarily removed / turned off.");

    QDir sourceDir(sourceDirPath);

    //
    // get everything, but handle only files and symlinks (pointing for other targets, like Drives)
    //

    QDir::Filters entryListFilters = QDir::NoDotAndDotDot | QDir::Files | QDir::Drives | QDir::Hidden | QDir::System;
    if(!isIgnoreDirectorySymlinks) {
        entryListFilters |= QDir::Dirs;
    }

    QStringList files = sourceDir.entryList(entryListFilters);
    for(int i = 0; i < files.count(); i++)
    {
        QString srcFullPath = PathHelper::combineAndCleanPathes(sourceDirPath, files[i]);
        QString destFullPath = PathHelper::combineAndCleanPathes(destDirPath, files[i]);

        // SYMLINKS

        // QFile cannot copy the file, when destName exists
        if(PathHelper::isSymlink(srcFullPath)) {
            // Symlink!
            DLogS << QString("Symlink found (%1) - target: (%2). Symlink-handling-mode: (%3) ").arg(srcFullPath).arg(QFileInfo(srcFullPath).symLinkTarget()).arg(symlinkHandlingMode);
//            WLog(QString("The file [%1] is a symlink to file [%2]").arg(srcName).arg( QFileInfo(srcName).symLinkTarget() ));

            if(symlinkHandlingMode == SHM_UseAsFile) {
                DLog(" - Symlink will be used as file, will be saved to path: ") << destFullPath;

#ifdef Q_OS_WIN
                // copy it as a normal file
                if(!QFile::copy(srcFullPath, destFullPath)) {
                    WLog(QString(" ! Cannot copy the symlink-file from [%1] to [%2]").arg(srcFullPath).arg(destFullPath));
                    return false;
                }
#endif

#ifdef Q_OS_MAC
//                if(QFileInfo(srcFullPath).symLinkTarget().isEmpty()) {
//                    WLog("Symlink found, but target is empty: ") << srcFullPath;
//                    continue;
//                }

//                QDir sourceDir(sourceDirPath);
                QString symlinkPath = getSymlinkTarget(QFileInfo(srcFullPath).absoluteFilePath());
                //sourceDir.relativeFilePath(QFileInfo(srcFullPath).symLinkTarget());

                DLog(QString("Symlink created at path %1 with target %2").arg(destFullPath).arg(symlinkPath));

                if( !QFile::link(symlinkPath, destFullPath) ) {
                    WLog("Symlink cannot be created!");
                    return false;
                }
#endif
            }
            else if(symlinkHandlingMode == SHM_UseAsTarget)
            {
                WLog(" - Symlink handling is set to 'UseAsTarget' - not yet implemented.");
//                QString linkTargetPath = QFileInfo(srcFullPath).symLinkTarget();
//                QFileInfo linkTargetFInfo(linkTargetPath);

//                if(linkTargetFInfo.isDir())
//                {
//                    // symlink target is a dir!
//                    DLog(" - Symlink target is a directory!");
//                    QDir linkTargetDir(linkTargetPath);
//                    if(!linkTargetDir.exists()) {
//                        WLog(" - Symlink target directory does NOT exists: ") << linkTargetPath;
//                    }
//                    QString destTargetDirPath = PathHelper::combineAndCleanPathes(destDirPath, linkTargetDir.dirName());
//                    DLog(" - Symlink dest target dir path: ") << destTargetDirPath;

//                    if(!PathHelper::copyWholeDirectory_recursive(srcFullPath, destTargetDirPath, symlinkHandlingMode, isFailWhenContentCopyFails)) {
//                        return false;
//                    }
//                }
//                else {
//                    DLog("Symlink target is a file: ") << linkTargetPath;
//                    QString destTargetFilePath = PathHelper::combineAndCleanPathes(destDirPath, linkTargetFInfo.fileName());
//                    DLog(" - Dest target File path: ") << destTargetFilePath;
//                    QFile::copy(linkTargetPath, destTargetFilePath);
//                }
            }
            else {
                DLog(" - Symlink ignored");
            }

        }

        else
        {
            // NOT symlink - handle only files
            if(QFileInfo(srcFullPath).isFile())
            {

                if(!QFile::copy(srcFullPath, destFullPath)) {
                    WLog(QString(" ! Cannot copy file from [%1] to [%2]").arg(srcFullPath).arg(destFullPath));
                    return false;
                }
                else {
#ifdef ENABLE_PATH_MANAGER_LOGGING
                    DLog(QString("Copy succeeded - file from [%1] to [%2]").arg(srcFullPath).arg(destFullPath));
#endif
                }
            }
            else {
                WLog("Not a symlink and not a file (will be ignored): ") << srcFullPath;
            }
        }
    }
    files.clear();

    return true;
}

bool PathHelper::copyWholeDirectory_recursive(QString sourceDirPath, QString destDirPath, SymlinkHandlingModeEnum symlinkHandlingMode, bool isFailWhenContentCopyFails)
{
#ifdef ENABLE_PATH_MANAGER_LOGGING
    DLog(QString("copyWholeDirectory_recursive - sourceDir:%1 | destDir:%2").arg(sourceDirPath).arg(destDirPath));
#endif

    QDir sourceDir(sourceDirPath);
    if(!sourceDir.exists()) {
        WLogS << " ! The specified source path does not exists: " << sourceDirPath;
        return false;
    }

    QDir destDir(destDirPath);
    if(!destDir.exists())
    {
        if(!PathHelper::ensureDirectoryCreated(destDirPath)) {
            WLogS << " ! The specified destination path cannot be created: " << destDirPath;
            return false;
        }
    }

    if(!PathHelper::copyOnlyFilesOfDirectory(sourceDirPath, destDirPath, symlinkHandlingMode, true)) {
        if(isFailWhenContentCopyFails) {
            return false;
        }
    }

    // and get sub-directories as well
    QStringList dirs = sourceDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::Hidden/* | QDir::NoSymLinks*/); // !!! No symlink folders allowed
    for(int i = 0; i < dirs.count(); i++)
    {
        QString srcDirFullPath = PathHelper::combineAndCleanPathes(sourceDirPath, dirs[i]);
        QString destDirFullPath = PathHelper::combineAndCleanPathes(destDirPath, dirs[i]);
        QFileInfo srcFInfo(srcDirFullPath);

        if(PathHelper::isSymlink(srcDirFullPath)) {
            DLog(QString(" - Symlink %1 found for target %2").arg(srcDirFullPath).arg(srcFInfo.symLinkTarget()));

            if(symlinkHandlingMode == SHM_UseAsFile) {
                // use as file

#ifdef Q_OS_WIN
                // copy it as a normal file
                if(!QFile::copy(srcDirFullPath, destDirFullPath)) {
                    WLog(QString(" ! Cannot copy the symlink-file from [%1] to [%2]").arg(srcDirFullPath).arg(destDirFullPath));
                    if(QFile::exists(destDirFullPath)) {
                        WLog("Dest file is already exists: ") << destDirFullPath;
                    }
                    return false;
                }
#endif


#ifdef Q_OS_MAC
//                if(QFileInfo(srcDirFullPath).symLinkTarget().isEmpty()) {
//                    WLog("Symlink found, but target is empty: ") << srcDirFullPath;
//                    continue;
//                }
                /////
                //QDir sourceDir(sourceDirPath);
                QString symlinkPath = getSymlinkTarget(QFileInfo(srcDirFullPath).absoluteFilePath());
                //sourceDir.relativeFilePath(srcFInfo.symLinkTarget());





                DLog(QString("Symlink created at path %1 with target %2").arg(destDirFullPath).arg(symlinkPath));

                /////

                if( !QFile::link(symlinkPath, destDirFullPath) ) {
                    WLog("Symlink cannot be created!");
                    if(isFailWhenContentCopyFails) {
                        WLog(" - Fail");
                        return false;
                    }
                }
#endif
            }
            else if(symlinkHandlingMode == SHM_UseAsTarget) {
                WLog("!!!!!!!! Not yet implemented! (will be ignored)");
            }
            else {
                DLog("Symlink handling mode: ignore.");
            }
        }
        else {
            if(!PathHelper::copyWholeDirectory_recursive(srcDirFullPath, destDirFullPath, symlinkHandlingMode, isFailWhenContentCopyFails)) {
                return false;
            }
        }
    }

    return true;
}

QString PathHelper::cleanThisPath(QString s)
{
    QString thePath = s.replace(QString("\\"), QString("/"));
    return QDir::cleanPath(thePath);
}

QString PathHelper::makePathPlatformDependent(QString path)
{
    QString thePath;
#ifdef Q_WS_WIN
    thePath = path.replace(QString("/"), QString("\\"));
#endif

#ifdef Q_WS_MAC
    thePath = path.replace(QString("\\"), QString("/"));
#endif
    return thePath;
}

QString PathHelper::combineAndCleanPathes(QString partOne, QString partTwo)
{
    QString fullPath = partOne + QString("/") + partTwo;
    fullPath = cleanThisPath(fullPath);

    return QDir::cleanPath(fullPath);
}

QString PathHelper::quotePath(QString originalPath)
{
    return QString("\"") + originalPath + QString("\"");
}

bool PathHelper::ensureDirectoryCreated(QString s)
{
    if(!QDir().exists(s)) {
        if( !QDir().mkpath(s) ) {
            WLogS << "Directory CANNOT be created: " << s;
            return false;
        } else {
#ifdef ENABLE_PATH_MANAGER_LOGGING
            DLogS << "Directory created: " << s;
#endif
        }
    } else {
#ifdef ENABLE_PATH_MANAGER_LOGGING
        DLogS << "Directory already exists: " << s;
#endif
    }

    return true;
}

bool PathHelper::isFileExistsAndItsReallyAFile(QString filePath)
{
    return (!filePath.isEmpty() && QFile(filePath).exists() && !QDir(filePath).exists());
}

bool PathHelper::isFileExecutable(QString filePath) {
#ifdef Q_WS_WIN
    return (PathHelper::isFileExistsAndItsReallyAFile(filePath) && filePath.endsWith(".exe", Qt::CaseInsensitive));
#endif

#ifdef Q_WS_MAC
    return filePath.endsWith(".app");
    return (QFile(filePath).exists() ||
            (QDir(filePath).exists() &&
             filePath.endsWith(".app", Qt::CaseInsensitive)));
#endif
}


// ------------------------------------
// --- permission related functions ---

#ifdef Q_WS_WIN
extern Q_CORE_EXPORT int qt_ntfs_permission_lookup; // required to NTFS permission lookup, see Qt documentation at QFile::setPermissions
#endif

bool PathHelper::copyFileFromResource(QString fileIdentifierInResource, QString targetFilePath, bool isSetCopiedFilePermissionToReadWrite)
{
    if(QFile::copy(fileIdentifierInResource, targetFilePath))
    {
        if(isSetCopiedFilePermissionToReadWrite)
        {
            if(PathHelper::setPermissionForFile(targetFilePath, QFile::WriteUser | QFile::WriteOwner | QFile::ReadOwner | QFile::ReadUser, true)) {
                return true;
            }
        }
        else {
            // if write permission is not required then we're done, successfully
            return true;
        }
    }

    return false;
}

#ifdef Q_OS_MAC

QString PathHelper::getBundleIdentifier(QString path) {
//    CFStringRef applicationPathStr = CFStringCreateWithCharacters(0,
//                                                                  reinterpret_cast<const UniChar *>(path.unicode()),
//                                                                  path.length());
//    CFURLRef bundleURL = CFURLCreateWithFileSystemPath(kCFAllocatorDefault,
//                                                       applicationPathStr,
//                                                       kCFURLPOSIXPathStyle,
//                                                       true);

//    CFBundleRef applicationBundle = CFBundleCreate(kCFAllocatorDefault,
//                                                   bundleURL);
//    CFRelease(applicationPathStr);
//    CFRelease(bundleURL);

//    if (applicationBundle == NULL)
//        return "";

//    // Get an instance of the non-localized keys.
//    CFDictionaryRef bundleInfoDict = CFBundleGetInfoDictionary(applicationBundle);

//    // If we succeeded, look for our property.
//    if ( bundleInfoDict == NULL )
//        return "";

//    CFStringRef identifier = (CFStringRef)CFDictionaryGetValue(bundleInfoDict,
//                                                               kCFBundleIdentifierKey);

//    QString bundleIdentifier = QStringHelper::CFStringToQString(identifier);
//    DLog("Bundle Identifier found (") << bundleIdentifier << ") at path: " << path;

//    CFRelease(applicationBundle);
//    return bundleIdentifier;
}

#endif

bool PathHelper::setPermissionForFile(QString targetFilePath, QFile::Permissions permission, bool addPermission) {
    // if copy succeeded, then grant write permission to the file
    //  (by default, when a file from resource copied it will be read-only)
#ifdef Q_WS_WIN
    qt_ntfs_permission_lookup++; // required to NTFS permission lookup, see Qt documentation at QFile::setPermissions
#endif
    QFile::Permissions finalPermissions = (addPermission ? QFile(targetFilePath).permissions() | permission : permission);
    if(QFile::setPermissions(targetFilePath, finalPermissions))
    {
        return true;
    }

    DLog("Set permission for file FAILED: ") << targetFilePath << permission << addPermission;
    return false;
}

bool PathHelper::setPermissionForFilesOfDirectory(const QString& baseDirPath, QFile::Permissions permission, bool addPermission, bool recursively)
{
    QDir baseDir(baseDirPath);
    QStringList qsl = baseDir.entryList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files | QDir::NoSymLinks | QDir::Hidden);

    for(int i = 0; i < qsl.count(); i++) {
        QString currentFilePath = PathHelper::combineAndCleanPathes(baseDirPath, qsl[i]);
        QFileInfo finfo(currentFilePath);

        // If we've found a directory
        if (finfo.isDir()) {
            // Call it recursively if we have to

            if (recursively) {
                if (!PathHelper::setPermissionForFilesOfDirectory(currentFilePath, permission, addPermission, recursively)) {
                    return false;   // Some error occured
                }
            }
        } else if (finfo.isFile()) {
            if(!PathHelper::setPermissionForFile(currentFilePath, permission, addPermission)) {
//                DLog("Set permission for file failed: ") << currentFilePath << permission << addPermission;
                return false;
            }
        }
    }

    return true;
}

#ifdef Q_OS_MAC
QString PathHelper::getSymlinkTarget(QString symlink, int buffSize) {
    if (buffSize > INT_MAX)
        return "";

    char buff[buffSize];
    ssize_t len = readlink(symlink.toStdString().c_str(),
                           buff,
                           sizeof(buff)-1);
    if (len != -1) {
        buff[len] = '\0';

        return QString(buff);
    } else {
        if (errno == EFAULT)
            return getSymlinkTarget(symlink, buffSize * 10);
        else
            return "";
    }
}
#endif

bool PathHelper::isSymlink(QString path) {
    QFileInfo fileInfo(path);

    return fileInfo.isSymLink()
#ifdef Q_OS_MAC
           && !getSymlinkTarget(fileInfo.absoluteFilePath()).isEmpty()
#endif
            ;
}
