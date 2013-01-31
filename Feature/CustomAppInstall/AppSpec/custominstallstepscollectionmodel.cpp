#include "custominstallstepscollectionmodel.h"

CustomInstallStepsCollectionModel::CustomInstallStepsCollectionModel()
{
}

void CustomInstallStepsCollectionModel::addInarg(QString alias, QString awValue) {
    _inargsMap[alias] = awValue;
}

void CustomInstallStepsCollectionModel::addStep(CustomInstallStepModel stepModel) {
    _steps.append(stepModel);
}

QList<CustomInstallStepModel> CustomInstallStepsCollectionModel::getSteps() const {
    return _steps;
}

QString CustomInstallStepsCollectionModel::getAwValueForInargAlias(QString inargAlias) {
    return _inargsMap.value(inargAlias);
}
