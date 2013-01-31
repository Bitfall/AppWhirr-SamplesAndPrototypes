#include "pathmanager.h"

#include <QDir>
#include <QFile>
//#include <QSettings>

// debug and utility
#include <QDebug>
#include <QCoreApplication>

PathManager::PathManager()
{
}

// -----------------------------------------------------------------
// --- utility functions to easy the work with Qt dirs and files ---

bool PathManager::deleteThisDirectoryAndEverythingBelow(QString topDirPath)
{
    {
        QDir topDir(topDirPath);

        if (!topDir.exists()) {
            WLog(QString("The given topDir does not exists: %1").arg(topDirPath));
            return true;
        }

        //First delete any files in the current directory
        QFileInfoList files = topDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files | QDir::Hidden | QDir::System/* | QDir::NoSymLinks*/);
        for(int i = 0; i < files.count(); i++)
        {
            QString currFileInPath = files.at(i).fileName();
            /*QString currFileAbsolutePath = files.at(i).absoluteFilePath();
        if(QFileInfo(currFileAbsolutePath).isSymLink()) {
            // it's a symlink simply remove it
            PATH_MANAGER_INTERNAL_LOG_TO_DATABASE(QString("The dir is a symlink file [%1]. Simply remove it.").arg(currDirAbsolutePath));
            QDir().remove(currDirAbsolutePath);
        }
        else */

            if( !topDir.remove(currFileInPath) ) {
                WLogS << " ! The specified file cannot be removed: " << currFileInPath;
                WLog(QString("The specified file cannot be removed: %1").arg(files.at(i).absoluteFilePath()));
                return false;
            }
        }

        //Now recursively delete any child directories
        QFileInfoList dirs = topDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Dirs);
        for(int i = 0; i < dirs.count(); i++)
        {
            QString currDirAbsolutePath = dirs.at(i).absoluteFilePath();
            if(QFileInfo(currDirAbsolutePath).isSymLink()) {
                // it's a symlink to a dir, simply remove this symlink file
                WLog(QString("The dir is a symlink file [%1]. Simply remove it.").arg(currDirAbsolutePath));
                QDir().remove(currDirAbsolutePath);
            }
            else if( !PathManager::deleteThisDirectoryAndEverythingBelow( currDirAbsolutePath ) ) {
                return false;
            }
        }
    }

    //Finally, remove empty top directory

//    if( !topDir.rmdir(topDir.path()) ) {
    if( !QDir().rmdir(topDirPath) ) {
        WLog(QString("The specified directory cannot be removed: %1. Maybe it's still not empty.").arg(topDirPath));
        return false;
    }

    return true;
}

bool PathManager::copyWholeDirectory(QString sourceDirPath, QString destDirPath, bool isCopyOnlyContentOfSource)
{
    if(!isCopyOnlyContentOfSource) {
        // copy the folder as well
        return PathManager::copyWholeDirectory_recursive(sourceDirPath, destDirPath);
    }

    // copy only the sub dirs
    QDir sourceDir(sourceDirPath);
    if(!sourceDir.exists()) {
        WLogS << " ! The specified source path does not exists: " << sourceDirPath;
        return false;
    }

    QStringList subDirs = sourceDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks);
    if(subDirs.isEmpty()) {
#ifdef ENABLE_PATH_MANAGER_LOGGING
        DLogS << "The specified source directory is empty.";
#endif
        return true;
    }

    for(int i = 0; i < subDirs.count(); i++)
    {
        QString srcName = PathManager::combineAndCleanPathes(sourceDirPath, subDirs[i]);
        QString destName = PathManager::combineAndCleanPathes(destDirPath, subDirs[i]);
        if(!PathManager::copyWholeDirectory_recursive(srcName, destName)) {
            return false;
        }
    }

    // also copy the files from sourceDirPath
    if(!PathManager::copyOnlyFilesOfDirectory(sourceDirPath, destDirPath)) {
        return false;
    }

    return true;
}

bool PathManager::copyOnlyFilesOfDirectory(QString sourceDirPath, QString destDirPath)
{
    FLAG_FOR_REVIEW_WITH_HINT("Should copy symlink / shortcut files as well?? Temporarily removed / turned off.");

    QDir sourceDir(sourceDirPath);

    QStringList files = sourceDir.entryList(QDir::NoDotAndDotDot | QDir::Files | QDir::NoSymLinks);
    for(int i = 0; i < files.count(); i++)
    {
        QString srcName = PathManager::combineAndCleanPathes(sourceDirPath, files[i]);
        QString destName = PathManager::combineAndCleanPathes(destDirPath, files[i]);

        // QFile cannot copy the file, when destName exists
        if(QFileInfo(srcName).isSymLink()) {
            // tmp, do nothing
            WLog(QString("The file [%1] is a symlink to file [%2]").arg(srcName).arg( QFileInfo(srcName).symLinkTarget() ));
        }
        else {
            if(!QFile::copy(srcName, destName)) {
                WLogS << " ! Cannot copy the file from: " << srcName << " to: " << destName;
                WLog(QString(" ! Cannot copy file from [%1] to [%2]").arg(srcName).arg(destName));
                return false;
            }
            else {
#ifdef ENABLE_PATH_MANAGER_LOGGING
                DLog(QString("Copy succeeded - file from [%1] to [%2]").arg(srcName).arg(destName));
#endif
            }
        }
    }
    files.clear();

    return true;
}

bool PathManager::copyWholeDirectory_recursive(QString sourceDirPath, QString destDirPath)
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
        if(!PathManager::ensureDirectoryCreated(destDirPath)) {
            WLogS << " ! The specified destination path cannot be created: " << destDirPath;
            return false;
        }
    }

    if(!PathManager::copyOnlyFilesOfDirectory(sourceDirPath, destDirPath)) {
        return false;
    }

    // and get sub-directories as well
    QStringList dirs = sourceDir.entryList(QDir::Dirs | QDir::NoDotAndDotDot | QDir::NoSymLinks); // !!! No symlink folders allowed
    for(int i = 0; i < dirs.count(); i++)
    {
        QString srcName = PathManager::combineAndCleanPathes(sourceDirPath, dirs[i]);
        QString destName = PathManager::combineAndCleanPathes(destDirPath, dirs[i]);
        if(!PathManager::copyWholeDirectory_recursive(srcName, destName)) {
            return false;
        }
    }

    return true;
}

QString PathManager::cleanThisPath(QString s)
{
    QString thePath = s.replace(QString("\\"), QString("/"));
    return QDir::cleanPath(thePath);
}

QString PathManager::makePathPlatformDependent(QString path)
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

QString PathManager::combineAndCleanPathes(QString partOne, QString partTwo)
{
    QString fullPath = partOne + QString("/") + partTwo;
    fullPath = cleanThisPath(fullPath);

    return QDir::cleanPath(fullPath);
}

QString PathManager::quotePath(QString originalPath)
{
    return QString("\"") + originalPath + QString("\"");
}

bool PathManager::ensureDirectoryCreated(QString s)
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

bool PathManager::isFileExistsAndItsReallyAFile(QString filePath)
{
    return (QFile(filePath).exists() && !QDir(filePath).exists());
}

bool PathManager::isFileExecutable(QString filePath) {
#ifdef Q_WS_WIN
    return PathManager::isFileExistsAndItsReallyAFile(filePath);
#endif

#ifdef Q_WS_MAC
    return (QFile(filePath).exists() ||
            (QDir(filePath).exists() &&
             filePath.endsWith(".app")));
#endif
}

bool PathManager::setPermissionForFilesOfDirectory(const QString& baseDirPath, QFile::Permissions permission, bool addPermission, bool recursively) {
    QDir baseDir(baseDirPath);
    QStringList qsl = baseDir.entryList(QDir::NoDotAndDotDot | QDir::Dirs | QDir::Files | QDir::NoSymLinks);

    for(int i = 0; i < qsl.count(); i++) {
        QString currentFilePath = PathManager::combineAndCleanPathes(baseDirPath, qsl[i]);
        QFileInfo finfo(currentFilePath);

        // If we've found a directory
        if (finfo.isDir()) {
            // Call it recursively if we have to

            if (recursively) {
                if (!PathManager::setPermissionForFilesOfDirectory(currentFilePath, permission, addPermission, recursively)) {
                    return false;   // Some error occured
                }
            }
        } else if (finfo.isFile()) {
            if(!PathManager::_setPermissionForFile(currentFilePath, permission, addPermission)) {
                return false;
            }
        }
    }

    return true;
}


#ifdef Q_WS_WIN
extern Q_CORE_EXPORT int qt_ntfs_permission_lookup; // required to NTFS permission lookup, see Qt documentation at QFile::setPermissions
#endif

bool PathManager::copyFileFromResource(QString fileIdentifierInResource, QString targetFilePath, bool isSetCopiedFilePermissionToReadWrite)
{
    if(QFile::copy(fileIdentifierInResource, targetFilePath))
    {
        if(isSetCopiedFilePermissionToReadWrite)
        {
            if(PathManager::_setPermissionForFile(targetFilePath, QFile::WriteUser | QFile::WriteOwner | QFile::ReadOwner | QFile::ReadUser, true)) {
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

bool PathManager::_setPermissionForFile(QString targetFilePath, QFile::Permissions permission, bool addPermission) {
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

    return false;
}
