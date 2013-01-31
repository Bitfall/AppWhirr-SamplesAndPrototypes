#include "backgroundframeworkcheck.h"

#include <QProcess>
#include <QFile>

#include "Common/Helpers/pathhelper.h"

BackgroundFrameworkCheck::BackgroundFrameworkCheck(QList<FrameworkCheckModel> frameworkModelsForCheck, QObject *parent) :
    QObject(parent),
    _frameworkModelsForCheck(frameworkModelsForCheck)
{
}

void BackgroundFrameworkCheck::startChecking()
{
    QList<FrameworkCheckModel> availableFrameworks;
    QList<FrameworkCheckModel> notFoundFrameworks;

    for(int i = 0; i < _frameworkModelsForCheck.size(); i++)
    {
        FrameworkCheckModel currFwCheckModel = _frameworkModelsForCheck[i];
        if(this->isThisFrameworkAvailable(currFwCheckModel)) {
            availableFrameworks.append(currFwCheckModel);
        }
        else {
            notFoundFrameworks.append(currFwCheckModel);
        }
    }

    Q_EMIT frameworksAvailable(availableFrameworks);
    Q_EMIT frameworksNotFound(notFoundFrameworks);
    Q_EMIT finishedWithChecking();
}

bool BackgroundFrameworkCheck::isThisFrameworkAvailable(FrameworkCheckModel frameworkCheckModel)
{
    // perform some checking
    if(frameworkCheckModel.getFrameworkInfo().getFrameworkId() <= 0) {
        WLog("Framework-id is not defined!");
    }
    if(frameworkCheckModel.getFrameworkCheckerAppPath().isEmpty() || !QFile::exists(frameworkCheckModel.getFrameworkCheckerAppPath())) {
        WLog("The framework-checker app-path is empty or invalid! ") << frameworkCheckModel.getFrameworkInfo().getFrameworkId() << frameworkCheckModel.getFrameworkInfo().getFrameworkPrintableName();
        return false;
    }
    if(frameworkCheckModel.getFrameworkResultFileDirPath().isEmpty()) {
        WLog("Result file dir path is empty!");
//        return false;
    }

    QString resultFileName = QString("%1-fwcheckresult.txt").arg(QString::number(frameworkCheckModel.getFrameworkInfo().getFrameworkId()));
    QString frameworkResultFilePath = PathHelper::combineAndCleanPathes(frameworkCheckModel.getFrameworkResultFileDirPath(), resultFileName);

    // test for the result file and remove it if exists
    if(QFile::exists(frameworkResultFilePath))
    {
        QFile resultFile(frameworkResultFilePath);
        if(!resultFile.remove()) {
            WLog("Cannot remove the existing result file!");
        }
        else {
            DLog("Succesfully removed the previous result file");
        }
    }

//    frameworkResultFilePath = PathHelper::makePathPlatformDependent(frameworkResultFilePath);
    DLog("Result file path: ") << frameworkResultFilePath;

    // run the related fw checker app
    QStringList fwCheckerAppArgs;
    fwCheckerAppArgs << "-outFilePath" << frameworkResultFilePath;

    QProcess process;
    process.start(frameworkCheckModel.getFrameworkCheckerAppPath(), fwCheckerAppArgs, QProcess::ReadOnly);
    process.waitForFinished(5000);

    // check the result
    if(process.exitCode() != 0) {
        WLog("Exit code not 0: ") << process.exitCode();
        return false;
    }

    DLog("Exit code 0!");

    // check the result file as well
    if(!QFile::exists(frameworkResultFilePath)) {
        WLog("FW check result file not found!");
        return false;
    }

    DLog("Testing the result file");
    QFile resultFile(frameworkResultFilePath);
    resultFile.open(QFile::ReadOnly);
    QByteArray resultDataFromFile = resultFile.readLine();
    resultFile.close();
    if(resultDataFromFile != "success") {
        WLog("FW check result file found but it's content is invalid: ") << resultDataFromFile;
        return false;
    }

    DLog("Result data from check result file is correct! FW is available!");
    return true;
}
