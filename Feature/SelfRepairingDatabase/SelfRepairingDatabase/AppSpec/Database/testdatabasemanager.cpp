#include "testdatabasemanager.h"

#include <QSqlQuery>
#include <QVariant>
#include "Common/PathManager/pathmanager.h"

TestDatabaseManager::TestDatabaseManager(QObject *parent) :
    SelfRepairingDatabase("test-db-connection", parent)
{
}

QString TestDatabaseManager::getDatabasePath() {
    static QString path("__testDatabase.db");
    return path;
}

bool TestDatabaseManager::copyDatabaseFromResourceToPath(QString path) {
    return PathManager::copyFileFromResource(":/testDatabase1", path, true);
}

// current desired scheme:
//  TABLE dynamicAppInfo (installedPath TEXT, installedVersion TEXT, isStartWhenClientStarts NUMERIC, grabbedIconPath TEXT, isHidden NUMERIC, supportedPlatformFlags TEXT)

DatabaseTableSchemeDescription TestDatabaseManager::_getRequiredSchemeDescriptionForTable(QString tableName)
{
    if(tableName == "dynamicAppInfo") {
        if(this->_dynamicAppInfoTableScheme.isEmpty()) {
            // build and store the table-sceme only if needed - this will save time and memory when not needed (hopefully in most of the times)
            this->_dynamicAppInfoTableScheme.addItem(DatabaseTableSchemeDescription::DatabaseTableSchemeDescriptionItem(-1, "installedPath", "TEXT UNIQUE"));
            this->_dynamicAppInfoTableScheme.addItem(DatabaseTableSchemeDescription::DatabaseTableSchemeDescriptionItem(-1, "installedVersion", "TEXT"));
            this->_dynamicAppInfoTableScheme.addItem(DatabaseTableSchemeDescription::DatabaseTableSchemeDescriptionItem(-1, "isStartWhenClientStarts", "NUMERIC"));
            this->_dynamicAppInfoTableScheme.addItem(DatabaseTableSchemeDescription::DatabaseTableSchemeDescriptionItem(-1, "grabbedIconPath", "TEXT"));
            this->_dynamicAppInfoTableScheme.addItem(DatabaseTableSchemeDescription::DatabaseTableSchemeDescriptionItem(-1, "isHidden", "NUMERIC"));
            this->_dynamicAppInfoTableScheme.addItem(DatabaseTableSchemeDescription::DatabaseTableSchemeDescriptionItem(-1, "supportedPlatformFlags", "TEXT"));
        }

        return this->_dynamicAppInfoTableScheme;
    }

    WLog("Invalid table name - empty description returned.");
    return DatabaseTableSchemeDescription();
}

bool TestDatabaseManager::getAllItems(QList<TestDatabaseManager::TestDatabaseItemModel> &outResultItems)
{
    if(this->_getAllItemsImplementation(outResultItems)) {
        // everything is fine, nothing more to do
        return true;
    }
    else {
        // query failed - try to repair it
        if(this->_tryToRepairTheDatabaseStructureOfTable("dynamicAppInfo")) {
            // repair finished with success, retry the query
            return this->_getAllItemsImplementation(outResultItems);
        }
        else {
            // couldn't repair the database
            return false;
        }
    }

    return false;
}

bool TestDatabaseManager::_getAllItemsImplementation(QList<TestDatabaseManager::TestDatabaseItemModel> &outResultItems)
{
    bool isSucceeded = true;

    {
        QSqlDatabase db = this->openDatabaseConnectionAndReturnDatabase();

        // get dynamic infos
        QString queryString("SELECT installedPath, installedVersion, isStartWhenClientStarts, isHidden FROM dynamicAppInfo LIMIT 1");

        QSqlQuery queryForDyn(db);
        queryForDyn.prepare(queryString);
        if(!queryForDyn.exec()) {
            this->logQueryExecutionFailedWithLastError(db);
            isSucceeded = false;
        }
        else {
            while(queryForDyn.next())
            {
            QString installedPath = queryForDyn.value(0).toString();
            QString installedVersion = queryForDyn.value(1).toString();
            bool isStartWhenClientStarts = queryForDyn.value(2).toBool();
            bool isHidden = queryForDyn.value(3).toBool();

            QString grabbedIconPath = "nopath";
            QString supportedPlatformFlags = "-1";

            outResultItems.append(TestDatabaseManager::TestDatabaseItemModel(installedPath, installedVersion, isStartWhenClientStarts, grabbedIconPath, isHidden, supportedPlatformFlags));
            }
        }
    }

    this->closeDatabaseConnection();
    return isSucceeded;
}

bool TestDatabaseManager::addNewItem(TestDatabaseManager::TestDatabaseItemModel newItemModel)
{
    if(this->_addNewItemImplementation(newItemModel)) {
        // everything is fine, nothing more to do
        return true;
    }
    else {
        // query failed - try to repair it
        if(this->_tryToRepairTheDatabaseStructureOfTable("dynamicAppInfo")) {
            // repair finished with success, retry the query
            return this->_addNewItemImplementation(newItemModel);
        }
        else {
            // couldn't repair the database
            return false;
        }
    }

    return false;
}

bool TestDatabaseManager::_addNewItemImplementation(TestDatabaseManager::TestDatabaseItemModel newItemModel)
{
    return false;
}
