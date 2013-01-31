#ifndef PATHHELPER_H
#define PATHHELPER_H

#include <QString>
#include <QFile>
#include <QList>

QT_BEGIN_NAMESPACE
class QDir;
QT_END_NAMESPACE

class PlatformspecificRunningExecutableDataInterface;

//
// the get..DirectoryPath() methods have to create the directory if it does not exists - call ensureDirectoryCreated(). If it cannot create the directory it has to return "failed" (usually empty string)
class PathHelper
{
private:
    PathHelper();

public:
    enum SymlinkHandlingModeEnum {
        SHM_Ignore = 0,
        SHM_UseAsFile = 1,
        SHM_UseAsTarget = 2
    };

public:    

    // -----------------------------------------------
    // --- system specific directories and pathers ---

    static QString getLocalDesktopPath();

#ifdef Q_WS_WIN
    static QString getWinSpecStartupPath();
    static QString getWinSpecStartMenuPath();
    static QString getWinSpecProgramFilesPath();
#endif


    // -----------------------------------------------------------------
    // --- utility functions to easy the work with Qt dirs and files ---
    //
    //  [!] these will skip SymLink files. The only exception is delete - this will delete the symlink file as well, but won't delete the files at the symlink's target (if that's a directory) - required by security


    //
    // Qt doesn't provide a simple method to remove directories which are not empty. This method makes it happen.
    // [!] It's a recursive function
    //  [!] Symlinks will be handled as files - only the symlink files will be deleted, not the targets
    static bool deleteThisDirectoryAndEverythingBelow(QString topDirPath);

    //
    // Qt doesn't provide a simple method to copy whole directories. This method makes it happen.
    // [!] It's a recursive function
    //  [!] It won't affect symlink / shortcut files. Simply skips them.
    //
    // If isFailWhenContentCopyFails is true then it will return false at the first content copy error
    //  if it's false then it will move forward and skip the problematic file
    //  in both cases it will return false if the sourceDir does not exists
    static bool copyWholeDirectory(QString sourceDirPath, QString destDirPath, bool isCopyOnlyContentOfSource, SymlinkHandlingModeEnum symlinkHandlingMode, bool isFailWhenContentCopyFails = true);

    //
    // this will convert the given path to the current platform's format
    //  on Windows it will replace / with \ and on Mac it will replace \ with / character
    static QString makePathPlatformDependent(QString path);

    //
    // combines the 2 path and returns the normalized combination of them
    static QString combineAndCleanPathes(QString partOne, QString partTwo);

    //
    // normalizes the path (replaces '\'s with '/'s, and cleans the path - based on QDir::cleanPath - resolves system-links, ., .., etc.
    static QString cleanThisPath(QString s);

    //
    // QDir .exists returns true even if the specified path is not a directory but a file
    //  this function will return true only if the given path is really a file
    static bool isFileExistsAndItsReallyAFile(QString filePath);

    static bool isFileExecutable(QString filePath);

    //
    // Converts the input path to a safe path. E.g. it adds " -s around the path to allow spaces in it
    //  for programs can't do it automatically (e.g. command line - QProcess)
    // [!] But be aware that Qt may can't handle this safe-path.
    //  And if you use QProcess then it will add the quotes to arguments automatically,
    //      but not to the program's name!
    static QString quotePath(QString originalPath);

    //
    // Sets the file permission of the given basePath
    // Can be recursively - to this basePath have to be a directory and set recursively to true
    // Also it can add or modify (set) the permission
    static bool setPermissionForFilesOfDirectory(const QString& baseDirPath, QFile::Permissions permission, bool addPermission, bool recursively);
    static bool setPermissionForFile(QString targetFilePath, QFile::Permissions permission, bool addPermission);



    static bool ensureDirectoryCreated(QString s);


    //
    // tries to copy a file from resource to the specified path
    //  if isSetCopiedFilePermissionToReadWrite is true, then it will try to set the new, copied file's permission to read-write
    //      if the permission-setting is fails, then it will delete the intermediate (read-only) file and returns false
    //  if isSetCopiedFilePermissionToReadWrite is false, then it just tries to copy the resource to the specified path
    //  in both cases it will return false if the copying cannot be performed
    //      (if isSetCopiedFilePermissionToReadWrite is true than it will set read-write to User and Owner)
    static bool copyFileFromResource(QString fileIdentifierInResource, QString targetFilePath, bool isSetCopiedFilePermissionToReadWrite = true);

#ifdef Q_OS_MAC
    static QString getBundleIdentifier(QString path);
    static QString getSymlinkTarget(QString symlink, int buffSize = 1024);
#endif

    static bool isSymlink(QString path);

private:
    //
    // If isFailWhenContentCopyFails is true then it will return false at the first content copy error
    //  if it's false then it will move forward and skip the problematic file
    //  in both cases it will return false if the sourceDir does not exists
    static bool copyWholeDirectory_recursive(QString sourceDirPath, QString destDirPath, SymlinkHandlingModeEnum symlinkHandlingMode, bool isFailWhenContentCopyFails);

    /*! Copies every file of the given directory - copies symlink files as well if \a symlinkHandlinghMode does not prevent it.

        If symlink handling is not set to ignore you have to specify \a isIgnoreDirectorySymlinks param. If you set \a isIgnoreDirectorySymlinks to true then it will skip symlinks pointing to directories. Use it if you handle symlinks-pointing-to-dirs with other methods.

        @note This method will copy files of the directory + every kind of symlink (pointing to System, Hidden, Drive, ... targets). It won't resolve the found symlinks, it will only copy the symlink file, not it's target.
    */
    static bool copyOnlyFilesOfDirectory(QString sourceDirPath, QString destDirPath, SymlinkHandlingModeEnum symlinkHandlingMode, bool isIgnoreDirectorySymlinks);

//    static bool _copySymlink()
};

#endif // PATHHELPER_H
