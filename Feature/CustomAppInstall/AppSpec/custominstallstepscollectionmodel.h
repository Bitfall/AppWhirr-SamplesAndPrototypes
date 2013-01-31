#ifndef CUSTOMINSTALLSTEPSCOLLECTIONMODEL_H
#define CUSTOMINSTALLSTEPSCOLLECTIONMODEL_H

#include <QString>
#include <QList>
#include <QMap>

#include "custominstallstepmodel.h"

class CustomInstallStepsCollectionModel
{
public:
    CustomInstallStepsCollectionModel();

    void addInarg(QString alias, QString awValue);
    void addStep(CustomInstallStepModel stepModel);

    QList<CustomInstallStepModel> getSteps() const;
    QString getAwValueForInargAlias(QString inargAlias);

private:
    QList<CustomInstallStepModel>   _steps;
    QMap<QString, QString>          _inargsMap;
};

#endif // CUSTOMINSTALLSTEPSCOLLECTIONMODEL_H
