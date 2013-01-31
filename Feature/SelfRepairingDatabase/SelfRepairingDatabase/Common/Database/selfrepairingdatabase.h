#ifndef SELFREPAIRINGDATABASE_H
#define SELFREPAIRINGDATABASE_H

#include "basedatabase.h"

//
// currently this class supports removing unnecessary columns and adding missing ones by column-name
//  ! won't check the column type, default value, or anything else, only the column titles !
//  ! also the current implementation can repair 1 table at a time !
//
// usage:
//  1) implement the _getRequiredSchemeDescription() method
//  2) when a query fails call the _tryToRepairTheDatabaseStructureOfTable
//
// advise:
//  * return query success in every operation method to allow testing of success - and in the case it fails call the repair method and retry
class SelfRepairingDatabase : public BaseDatabase
{
    Q_OBJECT
public:
    explicit SelfRepairingDatabase(QString connectionName, QObject *parent = 0);
    virtual ~SelfRepairingDatabase();

protected:
    //
    // returns whether it could repair the table or not
    //  ! if no missing or unnecessary columns found it will do nothing and will return false !
    bool _tryToRepairTheDatabaseStructureOfTable(QString tableNameToRepair);
    //
    virtual DatabaseTableSchemeDescription _getRequiredSchemeDescriptionForTable(QString tableName) = 0;
};

#endif // SELFREPAIRINGDATABASE_H
