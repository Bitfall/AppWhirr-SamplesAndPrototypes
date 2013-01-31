#ifndef TESTDATABASEMANAGER_H
#define TESTDATABASEMANAGER_H

#include "Common/Database/selfrepairingdatabase.h"

class TestDatabaseManager : public SelfRepairingDatabase
{
    Q_OBJECT

public:
    class TestDatabaseItemModel {
    public:
        explicit TestDatabaseItemModel() {}
        explicit TestDatabaseItemModel(QString installedPath, QString installedVersion, bool isStartWhenClientStarts, QString grabbedIconPath, bool isHidden, QString supportedPlatformFlags) :
            _installedPath(installedPath), _installedVersion(installedVersion), _isStartWhenClientStarts(isStartWhenClientStarts), _grabbedIconPath(grabbedIconPath), _isHidden(isHidden), _supportedPlatformFlags(supportedPlatformFlags)
        {}

        QString getInstalledPath() const { return _installedPath; }
        QString getInstalledVersion() const { return _installedVersion; }
        bool getIsStartWhenClientStarts() const { return _isStartWhenClientStarts; }
        QString getGrabbedIconPath() const { return _grabbedIconPath; }
        bool getIsHidden() const { return _isHidden; }
        QString getSupportedPlatformFlags() const { _supportedPlatformFlags; }

    private:
        QString _installedPath;
        QString _installedVersion;
        bool _isStartWhenClientStarts;
        QString _grabbedIconPath;
        bool _isHidden;
        QString _supportedPlatformFlags;
    };

public:
    explicit TestDatabaseManager(QObject *parent = 0);

    bool getAllItems(QList<TestDatabaseItemModel> &outResultItems);
    bool addNewItem(TestDatabaseItemModel newItemModel);

protected:
    DatabaseTableSchemeDescription _getRequiredSchemeDescriptionForTable(QString tableName);
    QString getDatabasePath();
    bool copyDatabaseFromResourceToPath(QString path);

private:
    bool _getAllItemsImplementation(QList<TestDatabaseItemModel> &outResultItems);
    bool _addNewItemImplementation(TestDatabaseItemModel newItemModel);

private:
    DatabaseTableSchemeDescription _dynamicAppInfoTableScheme;
};

#endif // TESTDATABASEMANAGER_H
