#include "basedatabase.h"
#include <QSqlError>
#include <QString>
#include <QSqlQuery>
#include <QDir>
#include <QVariant>

#include <QThread>

BaseDatabase::BaseDatabase(const QString& baseConnectionName, QObject *parent) :
    QObject(parent),
    _baseConnectionName(baseConnectionName)
{
}

BaseDatabase::~BaseDatabase() {
//    It's a warning causing the destructor:)
//    Qt forum sais it cannot be disabled with connection closing in a function:)
//    QSqlDatabasePrivate::removeDatabase: connection 'SortingDatabaseManager' is
//    still in use, all queries will cease to work

//    db.close();
//    this->closeDatabase();
//    QSqlDatabase::removeDatabase(finalconnectionname);

//    this->closeDatabaseConnection();
}

QString BaseDatabase::getFinalConnectionName(QString baseConnectionName)
{
    return baseConnectionName + QString("-%1").arg((int)(QThread::currentThread()));
}

QSqlDatabase BaseDatabase::openDatabaseConnectionAndReturnDatabase()
{
    bool isSucceeded = true;

    QSqlDatabase db;

    QString finalConnectionName = this->getFinalConnectionName(this->_baseConnectionName);

#ifdef ENABLE_DATABASE_OPERATION_LOGGING
    DLog(" -> Try to open database connection: ") << finalConnectionName;
#endif

    // Reuse database connection if able
    //  DON'T REUSE - this makes it non threadsafe!
    //  A connection can be safely used in only 1 thread!
//    if (QSqlDatabase::connectionNames().contains(finalConnectionName)) {
//        // Opens it automatically if connection is closed
//        db = QSqlDatabase::database(finalConnectionName);
//    } else {


        // Or create a new one, if none found with the specified name
        db = QSqlDatabase::addDatabase("QSQLITE", finalConnectionName);

        QString path(getDatabasePath());

        bool isAlreadyExists = false;
        if(QDir().exists(path)) {
            isAlreadyExists = true;
        }
        else {
            isAlreadyExists = this->copyDatabaseFromResourceToPath(path);
        }
        db.setDatabaseName(path);

        // Open database
        if(!db.open()) {
//            isSucceeded = false;
            WLog("Cannot open database: ") << path;
            return db; // cannot open the database
        } else {
#ifdef ENABLE_DATABASE_OPERATION_LOGGING
            DLog("Database opened at path: ") << path;
#endif
        }

        if(!isAlreadyExists)
        {
            isSucceeded = this->fillDatabaseWithBasicData(db);
        }
//    }

    return db;
}


void BaseDatabase::closeDatabaseConnection()
{
    QString finalConnectionName = this->getFinalConnectionName(this->_baseConnectionName);

#ifdef ENABLE_DATABASE_OPERATION_LOGGING
    DLog(" -> close database connection: ") << finalConnectionName;
#endif
//    db.close();

//    db.removeDatabase(finalConnectionName);
    QSqlDatabase::removeDatabase(finalConnectionName);
}

QString BaseDatabase::createSingleColumnSelectQueryString(QString tableName, QString valueColumnName, QString keyColumnName, QString keyFilterText, int limitResultToNumber)
{
    if(tableName.isEmpty() || valueColumnName.isEmpty()) {
        qDebug("invalid parameters");
        return QString(); // empty and null
    }

    QString queryString("SELECT %1 FROM %2");
    queryString = queryString.arg(valueColumnName).arg(tableName);
    if(!keyColumnName.isEmpty() && !keyFilterText.isEmpty()) {
        queryString = QString("%1 %2").arg(queryString).arg(QString(" WHERE %1='%2'").arg(keyColumnName).arg(keyFilterText));
    }

    if(limitResultToNumber > 0) {
        queryString = QString("%1 %2").arg(queryString).arg(QString(" LIMIT %1").arg(limitResultToNumber));
    }

    return queryString;
}

QSqlError BaseDatabase::getLastError(QSqlDatabase db)
{
    // If opening database has failed user can ask
    // error description by QSqlError::text()
    return db.lastError();
}

DatabaseTableSchemeDescriptor BaseDatabase::_getCurrentDatabaseSchemeDescriptionForTable(QString tableName)
{
    DatabaseTableSchemeDescriptor databaseSchemeDescr;

    {
        QSqlDatabase db = this->openDatabaseConnectionAndReturnDatabase();

        // get dynamic infos
        static QString queryString = QString("PRAGMA TABLE_INFO(%1)");

        QSqlQuery query(db);
        query.prepare( queryString.arg(tableName) );

        if(!query.exec()) {
            this->logQueryExecutionFailedWithLastErrorForQuery(query);
        }
        else {
            while (query.next())
            {
                // get column descriptions
                int cid = query.value(0).toInt();
                QString name = query.value(1).toString();
                QString type = query.value(2).toString();
                // add it to the scheme-description
                databaseSchemeDescr.addThisItem(DatabaseTableSchemeDescriptor::DatabaseTableSchemeDescriptorItem(cid, name, type));

#ifdef ENABLE_DATABASE_OPERATION_LOGGING
                DLog("Database scheme item: ") << cid << name << type;
#endif
            }
        }
    }

    this->closeDatabaseConnection();

    return databaseSchemeDescr;
}

// --------------------------------
// --- Utility query operations ---

bool BaseDatabase::executeThisQuery(QString queryString)
{
    bool isSucceeded = true;

    {
        QSqlDatabase db = this->openDatabaseConnectionAndReturnDatabase();

        QSqlQuery queryForDyn(db);
        queryForDyn.prepare(queryString);
        if(!queryForDyn.exec()) {
            this->logQueryExecutionFailedWithLastErrorForQuery(queryForDyn);
            isSucceeded = false;
        }
    }

    this->closeDatabaseConnection();
    return isSucceeded;
}

bool BaseDatabase::_dropThisTableAndCreateNew(QString tableName, DatabaseTableSchemeDescriptor tableSchemeDescription, bool isFailIfDropFails)
{
    // drop original table
    QString dropOriginalTableQueryString = QString("DROP TABLE %1").arg(tableName);
    if(!this->executeThisQuery(dropOriginalTableQueryString)) {
        WLog("Cannot drop the original table.");

        if(isFailIfDropFails) {
            return false;
        }
    }

    // create the new, required (corrected) table
    QString createRequiredTableQueryString = QString("CREATE TABLE %1 (%2)").arg(tableName).arg(tableSchemeDescription.getTableColumnNameAndTypeListString());
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


// ---------------------------
// --- Transaction helpers ---

bool BaseDatabase::executeInTransaction(QStringList queriesToExecuteInTransaction)
{
    bool isSucceeded = true;

    {
        QSqlDatabase db = this->openDatabaseConnectionAndReturnDatabase();

        // start transaction
        if(!db.transaction()) {
            this->__logQueryExecutionFailedWithLastErrorForQuery(db, "transaction()");
            isSucceeded = false;
        }

        if(isSucceeded) {
            // do the queries in the transaction
            for(int i = 0; i < queriesToExecuteInTransaction.size() && isSucceeded; i++) {
                QSqlQuery queryForCurrInTransaction(db);
                queryForCurrInTransaction.prepare(queriesToExecuteInTransaction[i]);
                if(!queryForCurrInTransaction.exec()) {
                    WLog("Query faild in transaction: ") << queriesToExecuteInTransaction[i];
                    this->logQueryExecutionFailedWithLastErrorForQuery(queryForCurrInTransaction);
                    isSucceeded = false;
                }
            }
        }

        if(isSucceeded) {
            // everything is fine - commit the transaction
            if(!db.commit()) {
                this->__logQueryExecutionFailedWithLastErrorForQuery(db, "commit()");
                isSucceeded = false;
            }
        }
        else {
            WLog("Rollback");
            if(!db.rollback()) {
                this->__logQueryExecutionFailedWithLastErrorForQuery(db, "rollback()");
            }
        }
    }

    this->closeDatabaseConnection();
    return isSucceeded;
}

// ----------------------------

void BaseDatabase::__logQueryExecutionFailedWithLastErrorForQuery(QSqlDatabase db, QString queryString)
{
    WLog("Query execution failed with error: ") << this->getLastError(db).text() << " [for query: " << queryString << "]";
}

void BaseDatabase::logQueryExecutionFailedWithLastErrorForQuery(QSqlQuery query)
{
    WLog("Query execution failed with error: ") << query.lastError().text() << " [for query: " << query.lastQuery() << "]";
}

bool BaseDatabase::_completelyDeleteDatabase()
{
    // Close database
    this->closeDatabaseConnection();

    QString path(getDatabasePath());

    return QFile::remove(path);
}

//QSqlDatabase BaseDatabase::getDatabase() {
//    return db;
//}
