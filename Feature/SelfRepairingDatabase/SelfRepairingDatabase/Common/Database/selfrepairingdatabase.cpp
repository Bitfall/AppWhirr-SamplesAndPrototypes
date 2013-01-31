#include "selfrepairingdatabase.h"

SelfRepairingDatabase::SelfRepairingDatabase(QString connectionName, QObject *parent) :
    BaseDatabase(connectionName, parent)
{
}

SelfRepairingDatabase::~SelfRepairingDatabase()
{

}

bool SelfRepairingDatabase::_tryToRepairTheDatabaseStructureOfTable(QString tableNameToRepair)
{
//    bool isSucceeded = true;

    // get current scheme
    DatabaseTableSchemeDescription currDatabaseSchemeDescr = this->_getCurrentDatabaseSchemeDescriptionForTable(tableNameToRepair);
    if(currDatabaseSchemeDescr.isEmpty()) {
        WLog("Invalid database scheme description (empty)!!!");
        return false;
    }

    QList<DatabaseTableSchemeDescription::DatabaseTableSchemeDescriptionItem> currDatabaseSchemeDescrItems = currDatabaseSchemeDescr.getItems();

    //
    // compare the current and the desired scheme and make a diff scheme description
    DatabaseTableSchemeDescription requiredTableSchemeDescription = this->_getRequiredSchemeDescriptionForTable(tableNameToRepair);

    if(requiredTableSchemeDescription.isEmpty()) {
        WLog("Required table scheme is empty - invalid, won't change the table.");
        return false;
    }

    // this common table scheme will contain the columns found in both the current and in the required table scheme as well
    DatabaseTableSchemeDescription commonTableSchemeDescription = currDatabaseSchemeDescr;

    // also collect the unnecessary columns to remove
//    QList<QString> removeTheseColumns;

    // ! currently this will only compare by column names and will ignore type, default value, ...
    int currItemCnt = currDatabaseSchemeDescrItems.size();
    for(int i = 0; i < currItemCnt; i++) {
        QString currColumnName = currDatabaseSchemeDescrItems[i].getName();

        // remove from the missing column name list
        if(!requiredTableSchemeDescription.isContainsItemWithName(currColumnName)) {
            // this column should be removed - it's not in the required table scheme
            DLog("Remove this (it's not in the required table): ") << currColumnName;
            commonTableSchemeDescription.removeOneByColumnName(currColumnName);
        }
    }

    QString requiredTableSchemeDescriptionColumnNameAndTypeListString = requiredTableSchemeDescription.getTableColumnNameAndTypeListString();

    if(commonTableSchemeDescription.isEmpty()) {
        WLog("Common table scheme is empty - everything will be deleted and the new required structure will be added.");

        // drop original table
        QString dropOriginalTableQueryString = QString("DROP TABLE %1").arg(tableNameToRepair);
        if(!this->executeThisQuery(dropOriginalTableQueryString)) {
            WLog("Cannot drop the original table.");
            return false;
        }

        // create the new, required (corrected) table
        QString createRequiredTableQueryString = QString("CREATE TABLE %1 (%2)").arg(tableNameToRepair).arg(requiredTableSchemeDescriptionColumnNameAndTypeListString);
#ifdef ENABLE_DATABASE_OPERATION_LOGGING
        DLog("Create required table query: ") << createRequiredTableQueryString;
#endif
        if(!this->executeThisQuery(createRequiredTableQueryString)) {
            WLog("Cannot create required table.");
            return false;
        }

        // nothing more to do
        return true;
    }

    //
    // some corrections needed

    QString commonTableSchemeDescriptionColumnNameAndTypeListString = commonTableSchemeDescription.getTableColumnNameAndTypeListString();
    QString commonTableSchemeDescriptionColumnNameListString = commonTableSchemeDescription.getTableColumnNameListString();
//    QString requiredTableSchemeDescriptionColumnNameListString = requiredTableSchemeDescription.getTableColumnNameListString();

    // create tmp table
    QString createTmpTableQueryString = QString("CREATE TABLE TEMP_TABLE(%1)").arg(commonTableSchemeDescriptionColumnNameAndTypeListString);
#ifdef ENABLE_DATABASE_OPERATION_LOGGING
    DLog("Create tmp table query: ") << createTmpTableQueryString;
#endif
    if(!this->executeThisQuery(createTmpTableQueryString)) {
        WLog("Cannot create temporary table.");
        return false;
    }

    // copy to tmp table
    QString copyToTmpTableQueryString = QString("INSERT INTO TEMP_TABLE SELECT %1 FROM %2").arg(commonTableSchemeDescriptionColumnNameListString).arg(tableNameToRepair);
#ifdef ENABLE_DATABASE_OPERATION_LOGGING
    DLog("Copy to tmp table query: ") << copyToTmpTableQueryString;
#endif
    if(!this->executeThisQuery(copyToTmpTableQueryString)) {
        WLog("Cannot copy to temporary table.");
        return false;
    }

    // drop original table
    QString dropOriginalTableQueryString = QString("DROP TABLE %1").arg(tableNameToRepair);
    if(!this->executeThisQuery(dropOriginalTableQueryString)) {
        WLog("Cannot drop the original table.");
        return false;
    }

    // create the new, required (corrected) table
    QString createRequiredTableQueryString = QString("CREATE TABLE %1 (%2)").arg(tableNameToRepair).arg(requiredTableSchemeDescriptionColumnNameAndTypeListString);
#ifdef ENABLE_DATABASE_OPERATION_LOGGING
    DLog("Create required table query: ") << createRequiredTableQueryString;
#endif
    if(!this->executeThisQuery(createRequiredTableQueryString)) {
        WLog("Cannot create required table.");
        return false;
    }

    // copy the common parts to the new table
    QString copyCommonDataToNewTableQueryString = QString("INSERT INTO %1 (%2) SELECT %3 FROM TEMP_TABLE").arg(tableNameToRepair, commonTableSchemeDescriptionColumnNameListString, commonTableSchemeDescriptionColumnNameListString);
#ifdef ENABLE_DATABASE_OPERATION_LOGGING
    DLog("Copy from tmp to required table query: ") << copyCommonDataToNewTableQueryString;
#endif
    if(!this->executeThisQuery(copyCommonDataToNewTableQueryString)) {
        WLog("Cannot create required table.");
        return false;
    }

    // drop tmp table
    QString dropTmpTableQueryString = QString("DROP TABLE TEMP_TABLE");
    if(!this->executeThisQuery(dropTmpTableQueryString)) {
        WLog("Cannot drop the tmp table.");
        return false;
    }

    return true;
}
