#ifndef CUSTOMAPPINSTALLMANAGER_H
#define CUSTOMAPPINSTALLMANAGER_H

#include <QObject>

#include "custominstallstepscollectionmodel.h"

class CustomAppInstallManager : public QObject
{
    Q_OBJECT
public:
    explicit CustomAppInstallManager(QObject *parent = 0);

    void performByFile(QString customInstallFilePath);

Q_SIGNALS:
    void finishedWithSuccess();
    void finishedWithError(QString errorMessage);

private:
    /*! Processes the custom-install-file

        Processes the custom-install-file (related to the \a customInstallFilePath parameter), fills the given \a outCustomInstallStepsCollectionModel object and returns an error message or an empty string if no error happened.

        @return An error message or and empty string (if no error happened).
    */
    QString _processFile(QString customInstallFilePath, CustomInstallStepsCollectionModel &outCustomInstallStepsCollectionModel);

    QString _createProcessingErrorMessage(QString errorMessage, int errorLine, int errorColumn);
};

#endif // CUSTOMAPPINSTALLMANAGER_H
