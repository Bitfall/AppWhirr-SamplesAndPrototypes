#ifndef BASEDATABASE_H
#define BASEDATABASE_H

#include <QObject>
#include <QSqlDatabase>

QT_BEGIN_NAMESPACE
class QSqlError;
class QString;
QT_END_NAMESPACE

#include "databasetableschemedescription.h"

//
// one of the virtual database-creation methods have to be implemented (if none of them implemented openDatabase() will always return false)
//
// note: you have to call openDatabaseConnectionAndReturnDatabase() before every (batch of) operation(s) you want to make (typically call this at the beginning of a method which will use the database) and you have to call closeDatabaseConnection() when you finished with the operations
//  the only exception is the fillDatabaseWithBasicData method, which gets the open database as a parameter, and have to use it, and is have to NOT call either openDatabaseConnectionAndReturnDatabase() or closeDatabaseConnection()
//  warning: you HAVE TO CLOSE the database even if you want to return earlier than the end of the method (e.g. if there were some errors)! don't forget to close the database!
//
// For usage informations check the Qt doc/help of the QSqlDatabase class, and use it that way. This base class has only some helper methods (basic query creation, loggin, ...) and unified database and connection opening/closing methods, but the QSqlDatabase and the query execution is done "the Qt way"
//
// ! After the database is opened successfully for the first time it will create the desired database at path specified by getDatabasePath() and it won't override it after this
//  so the creation is a critical point, if it creates the file at path returned by getDatabasePath() but does something wrong (for example it creates an empty file) it won't recreate it anymore !
//      -> For adding self-repairing capability use the SelfRepairingDatabase base class
//      -> or optionally you can delete the whole database with _completelyDeleteDatabase() but this is not advised (this will force to recreate the whole database next time and this is time consuming)
//
class BaseDatabase : public QObject
{
    Q_OBJECT

public:
    explicit BaseDatabase(const QString& connectionName, QObject *parent = 0);
    virtual ~BaseDatabase();

    //
    // this will completely delete the database, you won't be able to restore it
    bool _completelyDeleteDatabase();

protected:
    QSqlDatabase openDatabaseConnectionAndReturnDatabase();
    void closeDatabaseConnection();

    QSqlError getLastError(QSqlDatabase db);

    DatabaseTableSchemeDescription _getCurrentDatabaseSchemeDescriptionForTable(QString tableName);


    // --- Implement these!

    //
    // you have to implement this and return the database's path, where it will be stored
    virtual QString getDatabasePath() = 0;
    //
    // return whether it's succeeded
    virtual bool copyDatabaseFromResourceToPath(QString path) { return false; }
    //
    // return whether it's succeeded
    virtual bool fillDatabaseWithBasicData(QSqlDatabase databaseToFill) { return false; }

//    QSqlDatabase getDatabase();


    // --- Logging methods

    void logQueryExecutionFailedWithLastError(QSqlDatabase db);

    // --- Query creation helper methods

    //
    // tableName has to be specified
    // valueColumnName has to be specified
    QString createSingleColumnSelectQueryString(QString tableName, QString valueColumnName, QString keyColumnName = QString(), QString keyFilterText = QString(), int limitResultToNumber = -1);

    // --- And some basic utility query operations
    bool executeThisQuery(QString queryString);

    // --- Transaction handling
    bool executeInTransaction(QStringList queriesToExecuteInTransaction);

private:
//    QSqlDatabase            db;
    QString                 dbConnectionName;
};

#endif // BASEDATABASE_H
